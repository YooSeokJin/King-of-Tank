#pragma once
#include "Object.h"
#include "Viewing.h"
#include "Projection.h"

class Camera {
public:
    Camera(float fov = 45.0f, float aspect = float(width_) / float(height_),
        float nearPlane = 1.f, float farPlane = 500.f);
    ~Camera();
    void update(float frameTime);
    void followObject(std::shared_ptr<Object> target, const glm::vec3& offset = glm::vec3(0.0f, 3.0f, 5.0f));

    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveMatrix() const;

    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);

    void rotate(int deltaX, int deltaY);
    void adjustFov(float deltaFov);
    float getYaw() const { return yaw_; }
    glm::vec3 getForwardVector() const { return front_; }
    //
    glm::vec3 getPosition() const { return position_; }
private:
    glm::vec3 position_;
    glm::vec3 up_;
    glm::vec3 front_;

    Viewing viewModel_;        
    Projection projModel_;      

    const Object* targetObject_;
    const glm::vec3* cameraOffset_;

    float yaw_;
    float pitch_;
    float roll_;
    float sensitivity_;
    float smoothingSpeed_;
};
