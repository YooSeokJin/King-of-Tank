module;
#include "gl/glew.h"
#include "Scene.h"
#include "ShaderManager.h"

export module Renderer;
namespace Renderer {
    namespace {
        ShaderManager* sm = nullptr;
        bool initialized = false;
        void Draw(const std::shared_ptr<Mesh>& mesh, const glm::mat4& view, const glm::mat4& proj);
        void Delete_Buffer(const std::shared_ptr<Mesh>& mesh);
        void Clear_Color(const glm::vec4& bg);
        void Setup_Mesh(const std::shared_ptr<Mesh>& mesh);
    }
    export void Init(const Scene& scene);
    export void Rnderer_Scene(const Scene& scene, const glm::mat4& proj_, const glm::mat4& view_);
    export void End(const Scene& scene);

    export void Setup_Object(const std::shared_ptr<Object>& obj);

    export void Depth(bool& depth);
    export void Fill(bool& fill);
    export void Cull(bool& cull);
}
namespace Renderer {
    namespace {
        void Draw(const std::shared_ptr<Mesh>& mesh, const glm::mat4& view, const glm::mat4& proj) {
            if (!mesh) return;

            auto& shader = sm->getShader(mesh->get_ShaderName().c_str());
            glUseProgram(shader.getProgramID());
            glBindVertexArray(mesh->getVAO());

            // À¯´ÏÆû ¼³Á¤
            if (mesh->Color) {
                shader.setUniformVec4("u_Color", *mesh->Color);
            }
            else {
                shader.setUniformVec4("u_Color", colorPalette[8]);
            }
            shader.setUniformMatrix4fv("u_Model", mesh->get_modelTransform());
            shader.setUniformMatrix4fv("u_Viewing", view);
            shader.setUniformMatrix4fv("u_Projection", proj);
            size_t vertexCount = mesh->get_indices().size();

            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));

            glBindVertexArray(0);
            glUseProgram(0);
        }
        void Delete_Buffer(const std::shared_ptr<Mesh>& mesh) {
            GLuint VAO = mesh->getVAO();
            GLuint EBO = mesh->getEBO();
            GLuint VBO = mesh->getVBO();
            if (EBO != 0) glDeleteBuffers(1, &EBO);
            if (VBO != 0) glDeleteBuffers(1, &VBO);
            if (VAO != 0) glDeleteVertexArrays(1, &VAO);
        }

        void Clear_Color(const glm::vec4& bg)
        {
            glClearColor(bg.r, bg.g, bg.b, bg.a);

        }

        void Setup_Mesh(const std::shared_ptr<Mesh>& mesh) {
            glGenVertexArrays(1, &mesh->getVAO());
            glGenBuffers(1, &mesh->getVBO());

            glBindVertexArray(mesh->getVAO());
            std::vector<float> vertexData = mesh->assembleVertexData();

            glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO());
            glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

            const size_t stride = 8 * sizeof(float); // position, normal, texcoords 3 + 3 + 2

            // Position
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
            glEnableVertexAttribArray(0);
            // Normal
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
            // Texture Coordinate
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
            glEnableVertexAttribArray(2);

            glBindVertexArray(0);
        }
    }
    export void Init(const Scene& scene) {
        if (!sm) {
            sm = new ShaderManager();
            initialized = true;
        }
    }
    export void Rnderer_Scene(const Scene& scene, const glm::mat4& proj_, const glm::mat4& view_) {
        Clear_Color(scene.getBG());
        glm::mat4 proj = proj_;
        glm::mat4 view = view_;
        for (const auto& object : scene.getStaticObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                Draw(mesh, view, proj);
            }
        }
        for (const auto& object : scene.getObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                Draw(mesh, view, proj);

                object->DrawGrid(view, proj);
            }
        }
    }
    export void End(const Scene& scene) {
        if (!initialized) return;
        initialized = false;
        for (const auto& object : scene.getObjects()) {
            for (const auto& mesh : object->getMeshes()) {
                Delete_Buffer(mesh);
            }
        }
        delete sm;
        sm = nullptr;
    }
    export void Setup_Object(const std::shared_ptr<Object>& obj) {
        for (auto& mesh : obj->getMeshes()) {
            Setup_Mesh(mesh);
        }
    }
    export void Setup_Static_Object(const std::shared_ptr<Static_Object>& obj) {
        for (auto& mesh : obj->getMeshes()) {
            Setup_Mesh(mesh);
        }
    }
    export void Depth(bool& depth) {
        if (!depth) {
            glEnable(GL_DEPTH_TEST);
        }
        else {
            glDisable(GL_DEPTH_TEST);
        }
        depth = !depth;
    }
    export void Fill(bool& fill)
    {
        if (!fill) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        fill = !fill;
    }
    export void Cull(bool& cull)
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
}