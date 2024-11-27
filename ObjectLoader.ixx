module;
#include <memory>
#include <string>
#include "Mesh.h"
#include "Object.h"
export module ObjectLoader;

namespace ObjectLoader {
    namespace {
        void read_newline(char* str) {
            char* pos = strchr(str, '\n');
            if (pos != NULL)
                *pos = '\0';
        }

    }
    export std::vector<std::shared_ptr<Mesh>> Load_Meshes(const std::string& filename, const std::string& shaderName) {
        FILE* file;
        fopen_s(&file, filename.c_str(), "r");
        if (!file) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }

        std::vector<std::shared_ptr<Mesh>> meshes;
        std::shared_ptr<Mesh> currentMesh;

        char line[1024];
        while (fgets(line, sizeof(line), file)) {
            read_newline(line);
            if (line[0] == 'o') {
                if (currentMesh && !currentMesh->get_positions().empty()) {
                    meshes.push_back(currentMesh);
                }
                currentMesh = std::make_shared<Mesh>();
                currentMesh->set_ShaderName(shaderName);
            }
            // Vertex (v)
            else if (line[0] == 'v' && line[1] == ' ') {
                float x, y, z;

                if (sscanf_s(line + 2, "%f %f %f", &x, &y, &z) == 3) {
                    currentMesh->add_position(glm::vec3(x, y, z));
                }
            }

            // Normal (vn)
            else if (line[0] == 'v' && line[1] == 'n') {
                float nx, ny, nz;
                if (sscanf_s(line + 2, "%f %f %f", &nx, &ny, &nz) == 3) {
                    currentMesh->add_normal(glm::vec3(nx, ny, nz));
                }
            }

            // Texture Coordinate (vt)
            else if (line[0] == 'v' && line[1] == 't') {
                float u, v;
                if (sscanf_s(line + 2, "%f %f", &u, &v) == 2) {
                    currentMesh->add_texCoord(glm::vec2(u, v));
                }
            }

            // Face (f)
            else if (line[0] == 'f' && line[1] == ' ') {
                unsigned int v[4]{}, vn[4]{}, uv[4]{};

                int numScanned = sscanf_s(line + 2, "%u/%u/%u %u/%u/%u %u/%u/%u",
                    &v[0], &uv[0], &vn[0],
                    &v[1], &uv[1], &vn[1],
                    &v[2], &uv[2], &vn[2]
                );

                if (numScanned >= 9) {
                    currentMesh->add_indices(v[0] - 1);
                    currentMesh->add_indices(v[1] - 1);
                    currentMesh->add_indices(v[2] - 1);

                    currentMesh->add_normal_indices(vn[0] - 1);
                    currentMesh->add_normal_indices(vn[1] - 1);
                    currentMesh->add_normal_indices(vn[2] - 1);

                    currentMesh->add_texcoords_indices(uv[0] - 1);
                    currentMesh->add_texcoords_indices(uv[1] - 1);
                    currentMesh->add_texcoords_indices(uv[2] - 1);
                    if (numScanned == 12) {
                        currentMesh->add_indices(v[0] - 1);
                        currentMesh->add_indices(v[2] - 1);
                        currentMesh->add_indices(v[3] - 1);

                        currentMesh->add_normal_indices(vn[0] - 1);
                        currentMesh->add_normal_indices(vn[2] - 1);
                        currentMesh->add_normal_indices(vn[3] - 1);

                        currentMesh->add_texcoords_indices(uv[0] - 1);
                        currentMesh->add_texcoords_indices(uv[2] - 1);
                        currentMesh->add_texcoords_indices(uv[3] - 1);
                    }

                }
            }
        }
        if (currentMesh && !currentMesh->get_positions().empty()) {
            meshes.push_back(currentMesh);
        }

        fclose(file);
        return meshes;
    }

    export std::shared_ptr<Object> Load_Object(const std::string& filename, const std::string& shaderName) {
        std::shared_ptr<Object> obj = std::make_shared<Object>();
        auto meshes = Load_Meshes(filename, shaderName);
        for (auto& mesh : meshes) {
            obj->addMesh(mesh);
        }
        return obj;
    }
    export std::shared_ptr<Static_Object> Load_StaticObject(const std::string& filename, const std::string& shaderName) {
        std::shared_ptr<Static_Object> obj = std::make_shared<Static_Object>();
        auto meshes = Load_Meshes(filename, shaderName);
        for (auto& mesh : meshes) {
            obj->addMesh(mesh);
        }
        return obj;
    }
}