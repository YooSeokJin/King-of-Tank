#include "Camera.h"
#include <glm/gtx/compatibility.hpp>
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
    : proj(fov, aspect, nearPlane, farPlane), target(nullptr), offset(nullptr), position(0.f)
{
    pitch = roll = 0.f;
    yaw = 180.f;
    pitch = 20.f;
    sensitivity = 0.05f;
    up = glm::vec3(0.f, 1.f, 0.f);
    front = glm::vec3(0.f);
}

Camera::~Camera() {
    offset = nullptr;
    target = nullptr;
}

void Camera::update(float frameTime)
{
    glm::vec3 targetPos = target->getPosition();
    float radius = glm::length(offset->x);

    glm::vec3 newPos;
    newPos.x = targetPos.x + radius * cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newPos.y = targetPos.y + radius * sin(glm::radians(pitch));
    newPos.z = targetPos.z + radius * sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    position = glm::mix(position, newPos, frameTime * smoothingSpeed);

    front = glm::normalize(targetPos - position);
}

void Camera::followObject(std::shared_ptr<Object> target_, const glm::vec3& offset_) {
    target = target_.get();
    offset = &offset_;
    position = target->getPosition() + *offset;
}

glm::mat4 Camera::getViewMatrix() const {
    if (target) {
        return view.getViewMatrix(position, target->getPosition(), up);
    }
    else {
        return view.getViewMatrix(position, glm::vec3(0.f), up);
    }
}

glm::mat4 Camera::getPerspectiveMatrix() const {
    return proj.getPerspectiveMatrix();
}

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    proj.setPerspective(fov, aspect, nearPlane, farPlane);
}

void Camera::rotate(int deltaX, int deltaY)
{
    yaw += deltaX * sensitivity;
    pitch += deltaY * sensitivity;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    if (yaw >= 360.0f) yaw -= 360.0f;
    if (yaw < 0.0f) yaw += 360.0f;
}
void Camera::adjustFov(float deltaFov)
{
    proj.setFov(proj.getFov() + deltaFov);

    if (proj.getFov() < 10.0f) proj.setFov(10.0f);
    if (proj.getFov() > 90.0f) proj.setFov(90.0f);
}

