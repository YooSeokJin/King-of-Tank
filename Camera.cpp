#include "Camera.h"
#include <glm/gtx/compatibility.hpp>
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
    : projModel_(fov, aspect, nearPlane, farPlane), targetObject_(nullptr), cameraOffset_(nullptr), position_(0.f)
{
    pitch_ = roll_ = 0.f;
    yaw_ = 180.f;
    pitch_ = 20.f;
    sensitivity_ = 0.05f;
    up_ = glm::vec3(0.f, 1.f, 0.f);
    front_ = glm::vec3(0.f);
    smoothingSpeed_ = 6.f;
}

Camera::~Camera() {
    cameraOffset_ = nullptr;
    targetObject_ = nullptr;
}

void Camera::update(float frameTime)
{
    glm::vec3 targetPos = targetObject_->getPosition();
    float radius = glm::length(cameraOffset_->x);

    glm::vec3 newPos(0.f);
    newPos.x = targetPos.x + radius * cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    newPos.y = targetPos.y + radius * sin(glm::radians(pitch_));
    newPos.z = targetPos.z + radius * sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));

    position_ = glm::mix(position_, newPos, frameTime * smoothingSpeed_);

    front_ = glm::normalize(targetPos - position_);
}

void Camera::followObject(std::shared_ptr<Object> target, const glm::vec3& offset) {
    targetObject_ = target.get();
    cameraOffset_ = &offset;
    position_ = targetObject_->getPosition() + *cameraOffset_;
}

glm::mat4 Camera::getViewMatrix() const {
    if (targetObject_) {
        return viewModel_.getViewMatrix(position_, targetObject_->getPosition(), up_);
    }
    else {
        return viewModel_.getViewMatrix(position_, glm::vec3(0.f), up_);
    }
}

glm::mat4 Camera::getPerspectiveMatrix() const {
    return projModel_.getPerspectiveMatrix();
}

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    projModel_.setPerspective(fov, aspect, nearPlane, farPlane);
}

void Camera::rotate(int deltaX, int deltaY)
{
    yaw_ += deltaX * sensitivity_;
    pitch_ += deltaY * sensitivity_;

    pitch_ = glm::clamp(pitch_, 5.0f, 89.0f);
    if (yaw_ >= 360.0f) yaw_ -= 360.0f;
    if (yaw_ < 0.0f) yaw_ += 360.0f;
}
void Camera::adjustFov(float deltaFov)
{
    projModel_.setFov(projModel_.getFov() + deltaFov);

    if (projModel_.getFov() < 10.0f) projModel_.setFov(10.0f);
    if (projModel_.getFov() > 90.0f) projModel_.setFov(90.0f);
}

