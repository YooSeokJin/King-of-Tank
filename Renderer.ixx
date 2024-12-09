module;
#include "gl/glew.h"
#include "gl/freeglut.h"
#include "Scene.h"
#include "ShaderManager.h"

export module Renderer;
namespace Renderer {
    namespace {
        ShaderManager* M_shaderManager_ = nullptr;
        bool M_isInitialized_ = false;
        Shader* M_collisionShader_ = nullptr;
        bool M_isDrawAabb = false;
        void M_draw(const std::shared_ptr<Mesh>& mesh, const glm::mat4& view, const glm::mat4& proj, const Scene& scene);
        void M_deleteBuffer(const std::shared_ptr<Mesh>& mesh);
        void M_clearColor(const glm::vec4& bg);
        void M_setupMesh(const std::shared_ptr<Mesh>& mesh);
    }
    export void M_initRenderer(const Scene& scene);
    export void M_renderScene(const Scene& scene, const glm::mat4& proj_, const glm::mat4& view_);
    export void M_end(const Scene& scene);

    export void M_deleteObj(std::shared_ptr<Static_Object> obj);
    export void M_setupObject(const std::shared_ptr<Object>& obj);
    export void M_setupStaticObject(const std::shared_ptr<Static_Object>& obj);
    export void M_depthOnOff(bool& depth);
    export void M_fillOnOff(bool& fill);
    export void M_cullOnOff(bool& cull);
    export void m_collsionOnOff(bool& coll);
}
namespace Renderer {
    namespace {
        void M_draw(const std::shared_ptr<Mesh>& mesh, const glm::mat4& view, const glm::mat4& proj, const Scene& scene) {
            if (!mesh) return;

            auto& shader = M_shaderManager_->getShader(mesh->getShaderName().c_str());
            glUseProgram(shader.getProgramID());
            glBindVertexArray(mesh->getVAO());

            shader.setUniformMatrix4fv("u_Model", mesh->getModelTransform());
            shader.setUniformMatrix4fv("u_Viewing", view);
            shader.setUniformMatrix4fv("u_Projection", proj);

            // [TODO] need to be modified....
            shader.setUniformVec4("u_LightColor", colorPaletteV4_[36]); // Change Light Color!
            const glm::vec3 lightPos = glm::vec3(0.f, 10.0f, 0.f);
            shader.setUniformVec3("u_LightPos", lightPos);

            shader.setUniformVec3("u_ViewPos", scene.getCamera().getPosition());
            //===============================================================================
            size_t vertexCount = mesh->getIndices().size();

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
    }
    export void M_initRenderer(const Scene& scene) {
        if (!M_shaderManager_) {
            M_shaderManager_ = new ShaderManager();
            M_isInitialized_ = true;
            if (!scene.isShowMouse_) {
                glutSetCursor(GLUT_CURSOR_NONE);
            }
            glEnable(GL_BLEND);
            M_collisionShader_ = &M_shaderManager_->getShader("Collision");
        }
    }
    export void M_renderScene(const Scene& scene, const glm::mat4& proj_, const glm::mat4& view_) {
        M_clearColor(scene.getBackgroundColor());
        glm::mat4 proj = proj_;
        glm::mat4 view = view_;

        for (const auto& object : scene.getStaticObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                M_draw(mesh, view, proj, scene);
            }
        }
        for (const auto& object : scene.getObjects()) {
            object->drawGrid(view, proj);
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
    void m_collsionOnOff(bool& coll)
    {
        coll = !coll;
        M_isDrawAabb = coll;
    }
}