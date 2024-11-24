module;
#include "gl/glew.h"
#include <memory>
#include "Scene.h"
#include "glm/glm.hpp"
#include "ShaderManager.h"
#include "global.h"
#include "Mesh.h"
#include "Grid.h"

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
            auto& shader = sm->getShader(mesh->get_ShaderName().c_str());
            glUseProgram(shader.getProgramID());
            glBindVertexArray(mesh->getVAO());
            
            glm::mat4 model = mesh->get_modelTransform();
            shader.setUniformMatrix4fv("u_Model", model);
            shader.setUniformMatrix4fv("u_Viewing", view);
            shader.setUniformMatrix4fv("u_Projection", proj);

            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(mesh->get_indices().size()), GL_UNSIGNED_INT, nullptr);
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
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void Setup_Mesh(const std::shared_ptr<Mesh>& mesh) {
            glGenVertexArrays(1, &mesh->getVAO());
            glGenBuffers(1, &mesh->getVBO());
            glGenBuffers(1, &mesh->getEBO());

            glBindVertexArray(mesh->getVAO());

            std::vector<float> vertexData = mesh->assembleVertexData();
            const auto& indices = mesh->get_indices();

            glBindBuffer(GL_ARRAY_BUFFER, mesh->getVBO());
            glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getEBO());
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

            const size_t stride = 7 * sizeof(float); // 3, 4 position, color


            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

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