#include "Viewing.h"
#include "glm/gtc/matrix_transform.hpp"

Viewing::Viewing(glm::vec3 cameraPos, glm::vec3 cameraAt, glm::vec3 cameraUp)
    : cameraPos(cameraPos), cameraAt(cameraAt), cameraUp(cameraUp) {}

Viewing::~Viewing() {}

glm::mat4 Viewing::getViewMatrix() const {
    return glm::lookAt(cameraPos, cameraAt, cameraUp);
}

void Viewing::setCameraPosition(const glm::vec3& position) {
    cameraPos = position;
}

void Viewing::setCameraTarget(const glm::vec3& target) {
    cameraAt = target;
}

void Viewing::setCameraUp(const glm::vec3& up) {
    cameraUp = up;
}