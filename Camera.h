#pragma once
#include "glm/glm.hpp"
#include "Viewing.h"
#include "Projection.h"
#include "ModelMatrix.h"
#include "Object.h"
#include "Movement.h"
#include "memory"

class Camera {
public:
    Camera(float fov = 45.0f, float aspect = float(WinSizeX) / float(WinSizeY),
        float nearPlane = 0.1f, float farPlane = 100.0f);
    ~Camera();
    void update(float frameTime);
    void followObject(std::shared_ptr<Object> target, const glm::vec3& offset = glm::vec3(0.0f, 3.0f, -5.0f));

    glm::mat4 getViewMatrix() const;
    glm::mat4 getPerspectiveMatrix() const;

    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);
    void Add_Movement(float moveSpeed=5.f, float rtSpeed=30.f);
    void moveX(float dir);
    void moveZ(float dir);
    void Rotate_Y(float delta);
    void Camera_World_Rotate(float x, float y, float z);
    void Camera_World_Rotate_R(float x, float y, float z);

    void resetAll();
    bool allStop = false;
private:
    glm::vec3 Location;
   
    bool isRotate = false;
    bool isRotate_R = false;

    Viewing view;        
    Projection proj;      

    std::unique_ptr<ModelMatrix> model;
    std::unique_ptr<Movement> move;
    std::weak_ptr<Object> target;
    const glm::vec3* offset;

    std::weak_ptr<Object> view_target;

    bool isLocal = false;
};
