#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(float fov, float aspect, float nearPlane, float farPlane)
    : proj(fov, aspect, nearPlane, farPlane), target(), offset(nullptr) 
{
}

Camera::~Camera() {
    this->offset = nullptr;
}

void Camera::update(float frameTime)
{
    if (!model || !move) return;

    move->update(frameTime);
    model->setPivot(-offset->x, 0, 0);
    model->rotate(move->get_delta_rotation());
   
}

void Camera::followObject(std::shared_ptr<Object> target, const glm::vec3& offset) {
    this->target = target;
    this->offset = &offset;
}

glm::mat4 Camera::getViewMatrix() const {

	if (auto sharedTarget = target.lock()) {
        
        glm::vec3 cameraPos = sharedTarget->getPosition() + *offset;
		glm::vec3 targetPos = sharedTarget->getPosition();
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

		return glm::lookAt(cameraPos, targetPos, up);
	}

    return view.getViewMatrix();
}

glm::mat4 Camera::getPerspectiveMatrix() const {
    return proj.getPerspectiveMatrix();
}

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    proj.setPerspective(fov, aspect, nearPlane, farPlane);
}

void Camera::Add_Movement(float moveSpeed, float rtSpeed)
{
    move = std::make_unique<Movement>();
   
    move->set_velocity(moveSpeed, moveSpeed, moveSpeed);
    move->set_rt_velocity(rtSpeed, rtSpeed, rtSpeed);

    model = std::make_unique<ModelMatrix>();
    if (auto sharedTarget = target.lock()) {
        model->setLocation(sharedTarget->getPosition() - *offset);
    }
}

void Camera::moveX(float dir)
{
    model->translateX(dir);
}

void Camera::moveZ(float dir)
{
    model->translateZ(dir);
}

void Camera::Rotate_Y(float delta)
{
    model->rotateY(delta);
}

void Camera::Camera_World_Rotate(float x, float y, float z)
{
    printf("RT\n");
    if (!isRotate) {
        move->set_rt_direction(x, y, z);
    }
    else {
        move->set_rt_direction(0, 0, 0);
    }
    isRotate = !isRotate;
    if (isRotate_R) isRotate_R = false;
}

void Camera::Camera_World_Rotate_R(float x, float y, float z)
{
    printf("RT\n");
    if (!isRotate_R) {
        move->set_rt_direction(x, y, z);
    }
    else {
        move->set_rt_direction(0, 0, 0);
    }
    isRotate_R = !isRotate_R;
    if (isRotate) isRotate = false;
}

void Camera::resetAll()
{
    move->set_rt_direction(0, 0, 0);
    model->resetAll();
}

