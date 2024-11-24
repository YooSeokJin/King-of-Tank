#ifndef PROJECTION_H
#define PROEJCTION_H
#include "glm/mat4x4.hpp"
#include "global.h"
class Projection {
public:
    Projection(float fov = 45.0f, float aspect = float(WinSizeX) / float(WinSizeY), float nearPlane = 0.1f, float farPlane = 100.0f);
    ~Projection();

    glm::mat4 getPerspectiveMatrix() const;
    glm::mat4 getOrthographicMatrix() const;

    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);
    void setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

private:
    float fov, aspect, nearPlane, farPlane;
    float orthoLeft, orthoRight, orthoBottom, orthoTop;
};
#endif