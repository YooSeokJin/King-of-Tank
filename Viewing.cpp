#include "Viewing.h"
#include "glm/gtc/matrix_transform.hpp"

Viewing::Viewing()
{}

Viewing::~Viewing() {}

glm::mat4 Viewing::getViewMatrix(const glm::vec3& Pos, const glm::vec3& At, const glm::vec3& Up) const {
    return glm::lookAt(Pos, At, Up);
}
