#pragma once
#include "glm/mat4x4.hpp"
#include "global.h"
class Projection {
public:
    Projection(float fov = 45.0f, float aspect = float(width_) / float(height_), float nearPlane = 0.1f, float farPlane = 100.0f);
    ~Projection();

    glm::mat4 getPerspectiveMatrix() const;
    glm::mat4 getOrthographicMatrix() const;

    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);
    void setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

    void setFov(float newFov);
    float getFov() const { return fov_; }
private:
    float fov_, aspect_, nearPlane_, farPlane_;
    float orthoLeft_, orthoRight_, orthoBottom_, orthoTop_;
};
