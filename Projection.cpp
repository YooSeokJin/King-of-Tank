#include "Projection.h"
#include <glm/gtc/matrix_transform.hpp>


Projection::Projection(float fov, float aspect, float nearPlane, float farPlane)
    : fov(fov), aspect(aspect), nearPlane(nearPlane), farPlane(farPlane),
    orthoLeft(-1.0f), orthoRight(1.0f), orthoBottom(-1.0f), orthoTop(1.0f) 
{

}

Projection::~Projection() {}

glm::mat4 Projection::getPerspectiveMatrix() const {
    return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

glm::mat4 Projection::getOrthographicMatrix() const {
    return glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, nearPlane, farPlane);
}

void Projection::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    this->fov = fov;
    this->aspect = aspect;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}

void Projection::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    orthoLeft = left;
    orthoRight = right;
    orthoBottom = bottom;
    orthoTop = top;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}

void Projection::setFov(float newFov)
{
    fov = newFov;
}
