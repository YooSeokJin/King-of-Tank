#pragma once
#include "Object.h"
#include "Viewing.h"
#include "Projection.h"

class Camera {
public:
    Camera(float fov = 45.0f, float aspect = float(WinSizeX) / float(WinSizeY),
        float nearPlane = 0.1f, float farPlane = 100.0f);
    ~Camera();
    void update(float frameTime);
    void followObject(std::shared_ptr<Object> target, const glm::vec3& offset = glm::vec3(0.0f, 3.0f, 5.0f));

    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveMatrix() const;

    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);

    void rotate(int deltaX, int deltaY);
    void adjustFov(float deltaFov);
    float getYaw() const { return yaw; }
    glm::vec3 getForwardVector() const { return front; }
private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 front;

    Viewing view;        
    Projection proj;      

    const Object* target;
    const glm::vec3* offset;

    float yaw;
    float pitch;
    float roll;
    float sensitivity;
    float smoothingSpeed = 6.0f;
};
