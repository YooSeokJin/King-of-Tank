#pragma once
#include "glm/glm.hpp"

class Viewing {
public:
    Viewing();
    ~Viewing();

    glm::mat4 getViewMatrix(const glm::vec3& Pos, const glm::vec3& At, const glm::vec3& Up) const;
};