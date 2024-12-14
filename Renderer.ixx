module;
#include "gl/glew.h"
#include "gl/freeglut.h"
#include <fstream>
#include <iostream>
#include "Scene.h"
#include "ShaderManager.h"

export module Renderer;
namespace Renderer {
    namespace {
        ShaderManager* M_shaderManager_ = nullptr;
        bool M_isInitialized_ = false;
        Shader* M_collisionShader_ = nullptr;
        bool M_isDrawAabb = false;
        std::vector<GLuint> M_textures;
        void M_draw(const std::shared_ptr<Mesh>& mesh, const glm::mat4& view, const glm::mat4& proj, const Scene& scene);
        void M_deleteBuffer(const std::shared_ptr<Mesh>& mesh);

        void M_clearColor(const glm::vec4& bg);
        void M_setupMesh(const std::shared_ptr<Mesh>& mesh);
        void M_initTextures();
    }
    export void M_initRenderer(const Scene& scene);
    export void M_renderScene(const Scene& scene, const glm::mat4& proj_, const glm::mat4& view_);
    export void M_end(const Scene& scene);
    export void M_glViewport(int x, int y, int width, int height);
    export void M_clear(const glm::vec4& bgColor);

    export void M_deleteObj(std::shared_ptr<Static_Object> obj);
    export void M_setupObject(const std::shared_ptr<Object>& obj);
    export void M_setupStaticObject(const std::shared_ptr<Static_Object>& obj);
    export void M_depthOnOff(bool& depth);
    export void M_fillOnOff(bool& fill);
    export void M_cullOnOff(bool& cull);
    export void M_collisionOnOff(bool& coll);
}
namespace Renderer {
    namespace {
        void M_draw(const std::shared_ptr<Mesh>& mesh, const glm::mat4& view, const glm::mat4& proj, const Scene& scene) {
            glUseProgram(0);
            //if (!mesh) return;

            auto& shader = M_shaderManager_->getShader(mesh->getShaderName().c_str());
            glUseProgram(shader.getProgramID());
            glBindVertexArray(mesh->getVAO());

            shader.setUniformMatrix4fv("u_Model", mesh->getModelTransform());
            shader.setUniformMatrix4fv("u_Viewing", view);
            shader.setUniformMatrix4fv("u_Projection", proj);

            shader.setUniformVec4("u_Material.ambient", glm::vec4(0.25f, 0.25f, 0.25f, 1.0f));
            shader.setUniformVec4("u_Material.diffuse", glm::vec4(0.4f, 0.4f, 0.4f, 1.0f));
            shader.setUniformVec4("u_Material.specular", glm::vec4(0.774597f, 0.774597f, 0.774597f, 1.0f));;
            shader.setUniformFloat("u_Material.shininess", 1.0f);

            // 미니맵 라이트 효과를 제거할 방법을 ..
            // [TODO] need to be modified....
            // shader.setUniformVec3("u_Light.position", glm::vec3(0.f, 30.0f, 0.f));
            shader.setUniformVec3("u_Light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
            shader.setUniformVec4("u_Light.ambient", colorPaletteV4_[36]);
            shader.setUniformVec4("u_Light.diffuse", glm::vec4(0.4f, 0.4f, 0.4f, 1.f));
            shader.setUniformVec4("u_Light.specular", glm::vec4(1.f, 1.f, 1.f, 1.f));

            shader.setUniformVec3("u_ViewPos", scene.getCamera().getPosition());

            //===============================================================================
            size_t vertexCount = mesh->getIndices().size();

            if (mesh->textureType_ >= 0) {
                shader.setUniformInt("u_ResolX", mesh->resolX_);
                shader.setUniformInt("u_ResolY", mesh->resolY_);

                shader.setUniformInt("u_Material.diffuse", mesh->textureType_);
                shader.setUniformInt("u_Material.specular", mesh->textureType_);
                glActiveTexture(GL_TEXTURE0 + mesh->textureType_);
                glBindTexture(GL_TEXTURE_2D, M_textures[mesh->textureType_]);
            }

            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));

            glBindVertexArray(0);
            glUseProgram(0);
        }
        void M_deleteBuffer(const std::shared_ptr<Mesh>& mesh) {
            printf("Del Buffer\n");
            GLuint VAO = mesh->getVAO();
            GLuint EBO = mesh->getEBO();
            GLuint VBO = mesh->getVBO();
            if (EBO != 0) glDeleteBuffers(1, &EBO);
            if (VBO != 0) glDeleteBuffers(1, &VBO);
            if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        }

        void M_clearColor(const glm::vec4& bg) {
            glClearColor(bg.r, bg.g, bg.b, bg.a);
        }

        void M_setupMesh(const std::shared_ptr<Mesh>& mesh) {
            glGenVertexArrays(1, &mesh->getVAO());
            glGenBuffers(1, &mesh->getVBO());

            glBindVertexArray(mesh->getVAO());
            std::vector<float> vertexData = mesh->assembleVertexData();

            glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO());
            glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

            const size_t stride = 12 * sizeof(float); // position, normal, texcoords, Color 3 + 3 + 2 + 4

            // Position
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);
            // Normal
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            // Texture Coordinate
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);
            // Color
            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(float)));
            glEnableVertexAttribArray(3);

            glBindVertexArray(0);
        }
        void M_initTextures() {
            const char* textureFiles[] = { "./textures/camo.jpg", "./textures/ground.jpg", "./textures/wall.jpg" }; // 텍스처 파일 경로 배열
            const int textureCount = sizeof(textureFiles) / sizeof(textureFiles[0]); // 텍스처 개수

            unsigned int tex[textureCount];
            int width, height, nrChannels;

            glGenTextures(textureCount, tex);

            for (int i = 0; i < textureCount; ++i) {
                glBindTexture(GL_TEXTURE_2D, tex[i]);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                unsigned char* data = stbi_load(textureFiles[i], &width, &height, &nrChannels, 0);
                if (data) {
                    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
                    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else {
                    std::cout << "Failed to load texture: " << textureFiles[i] << std::endl;
                }

                stbi_image_free(data);

                M_textures.push_back(tex[i]);
            }
        }
    }
    export void M_initRenderer(const Scene& scene) {
        if (!M_shaderManager_) {
            M_shaderManager_ = new ShaderManager();
            M_isInitialized_ = true;
            if (!scene.isShowMouse_) {
                glutSetCursor(GLUT_CURSOR_NONE);
            }
            glEnable(GL_BLEND);
            M_initTextures();
            M_collisionShader_ = &M_shaderManager_->getShader("Collision");
        }
    }
    export void M_renderScene(const Scene& scene, const glm::mat4& proj_, const glm::mat4& view_) {
        if (!M_isInitialized_) return;
        glm::mat4 proj = proj_;
        glm::mat4 view = view_;

        for (const auto& object : scene.getStaticObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                M_draw(mesh, view, proj, scene);
                if (M_isDrawAabb) {
                    mesh->drawAabb(view, proj, *M_collisionShader_);
                }
            }
        }
        for (const auto& object : scene.getObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                M_draw(mesh, view, proj, scene);
                if (M_isDrawAabb) {
                    mesh->drawAabb(view, proj, *M_collisionShader_);
                }
            }
        }
        for (const auto& bullet : scene.getBullets()) {
            for (const auto& mesh : bullet->getMeshes()) {
                M_draw(mesh, view, proj, scene);
                if (M_isDrawAabb) {
                    mesh->drawAabb(view, proj, *M_collisionShader_);
                }
            }
        }
        for (const auto& line : scene.getLines()) {
            line->draw(view, proj);
        }
    }
    export void M_end(const Scene& scene) {
        if (!M_isInitialized_) return;
        M_isInitialized_ = false;
        for (const auto& object : scene.getObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                M_deleteBuffer(mesh);
            }
        }
        for (const auto& object : scene.getStaticObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                M_deleteBuffer(mesh);
            }
        }
        for (const auto& bullet : scene.getBullets()) {
            for (const auto& mesh : bullet->getMeshes()) {
                M_deleteBuffer(mesh);
            }
        }
        delete M_shaderManager_;
        M_shaderManager_ = nullptr;
    }
    void M_glViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }
    void M_clear(const glm::vec4& bgColor)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        M_clearColor(bgColor);
    }
    export void M_deleteObj(std::shared_ptr<Static_Object> obj)
    {
        for (auto& mesh : obj->getMeshes()) {
            M_deleteBuffer(mesh);
        }
    }
    void M_setupObject(const std::shared_ptr<Object>& obj) {
        for (auto& mesh : obj->getMeshes()) {
            M_setupMesh(mesh);
        }
    }
    export void M_setupStaticObject(const std::shared_ptr<Static_Object>& obj) {
        for (auto& mesh : obj->getMeshes()) {
            M_setupMesh(mesh);
        }
    }
    export void M_depthOnOff(bool& depth) {
        if (!depth) {
            glEnable(GL_DEPTH_TEST);
        }
        else {
            glDisable(GL_DEPTH_TEST);
        }
        depth = !depth;
    }
    export void M_fillOnOff(bool& fill)
    {
        if (!fill) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        fill = !fill;
    }
    export void M_cullOnOff(bool& cull)
    {
        if (!cull) {
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }
        else {
            glDisable(GL_CULL_FACE);
        }
        cull = !cull;
    }
    void M_collisionOnOff(bool& coll)
    {
        coll = !coll;
        M_isDrawAabb = coll;
    }

}