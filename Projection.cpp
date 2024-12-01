#include "Projection.h"
#include <glm/gtc/matrix_transform.hpp>


Projection::Projection(float fov, float aspect, float nearPlane, float farPlane)
    : fov_(fov), aspect_(aspect), nearPlane_(nearPlane), farPlane_(farPlane),
    orthoLeft_(-1.0f), orthoRight_(1.0f), orthoBottom_(-1.0f), orthoTop_(1.0f) 
{

}

Projection::~Projection() {}

glm::mat4 Projection::getPerspectiveMatrix() const {
    return glm::perspective(glm::radians(fov_), aspect_, nearPlane_, farPlane_);
}

glm::mat4 Projection::getOrthographicMatrix() const {
    return glm::ortho(orthoLeft_, orthoRight_, orthoBottom_, orthoTop_, nearPlane_, farPlane_);
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
