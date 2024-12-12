#include "Projection.h"
#include <glm/gtc/matrix_transform.hpp>


Projection::Projection(float fov, float aspect, float nearPlane, float farPlane)
    : fov_(fov), aspect_(aspect), nearPlane_(nearPlane), farPlane_(farPlane),
    orthoLeft_(-50.0f), orthoRight_(50.0f), orthoBottom_(-50.0f), orthoTop_(50.0f) 
{

}

Projection::~Projection() {}

glm::mat4 Projection::getPerspectiveMatrix() const {
    return glm::perspective(glm::radians(fov_), aspect_, nearPlane_, farPlane_);
}

glm::mat4 Projection::getOrthographicMatrix() const {
    return glm::ortho(-50.f, 50.f, -50.f, 50.f, 1.f, 100.f);
}

void Projection::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    this->fov_ = fov;
    this->aspect_ = aspect;
    this->nearPlane_ = nearPlane;
    this->farPlane_ = farPlane;
}

void Projection::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    orthoLeft_ = left;
    orthoRight_ = right;
    orthoBottom_ = bottom;
    orthoTop_ = top;
    this->nearPlane_ = nearPlane;
    this->farPlane_ = farPlane;
}

void Projection::setFov(float newFov)
{
    fov_ = newFov;
}
