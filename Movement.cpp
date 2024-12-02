#include "Movement.h"

Movement::Movement()
    : velocity_(6.f, 6.f, 6.f), direction_(0.f), deltaPosition_(0.f),
    rotationVelocity_(30.f), rotationDirection_(0.f), deltaRotation_(0.f)
{
}
void Movement::update(float frameTime)
{
    deltaPosition_ = direction_ * velocity_ * frameTime;
    deltaRotation_ = rotationDirection_ * rotationVelocity_ * frameTime;
}
void Movement::setVelocity(float vx, float vy, float vz)
{
    glm::vec3 v(vx, vy, vz);
    velocity_ = glm::vec3(v);
}
void Movement::setRtVelocity(float vx, float vy, float vz)
{
    glm::vec3 v(vx, vy, vz);
    rotationVelocity_ = v;
}

void Movement::addDirection(float dx, float dy, float dz)
{
    glm::vec3 d(dx, dy, dz);
    direction_ += d;
}

void Movement::addRtDirection(float dx, float dy, float dz)
{
    glm::vec3 rd(dx, dy, dz);
    rotationDirection_ += rd;
}

void Movement::setDirection(float dx, float dy, float dz)
{
    glm::vec3 d(dx, dy, dz);
    if (glm::length(d) > 0.0f) {
        direction_ = glm::normalize(d);
    }
    else {
        direction_ = glm::vec3(0.0f);
    }
}

void Movement::setDirectionX(float delta)
{
    direction_.x = delta;
}

void Movement::setDirectionY(float delta)
{
    direction_.y = delta;
}

void Movement::setDirectionZ(float delta)
{
    direction_.z = delta;
}

void Movement::setRtDirection(float dx, float dy, float dz)
{
    glm::vec3 d(dx, dy, dz);
    if (glm::length(d) > 0.0f) {
        rotationDirection_ = glm::normalize(d);
    }
    else {
        rotationDirection_ = glm::vec3(0.0f);
    }
}

void Movement::setRtDirectionX(float delta)
{
    rotationDirection_.x = delta;
}

void Movement::setRtDirectionY(float delta)
{
    rotationDirection_.y = delta;
}

void Movement::setRtDirectionZ(float delta)
{
    rotationDirection_.z = delta;
}

const glm::vec3& Movement::getDeltaPosition()
{
    return deltaPosition_;
}

const glm::vec3& Movement::getDeltaPosition(float dx, float dz)
{
    deltaPosition_.x *= dx;
    deltaPosition_.z *= dz;
    return deltaPosition_;
}

const glm::vec3& Movement::getDeltaRotation()
{
    return deltaRotation_;
}

void Movement::stop()
{
    rotationDirection_ = glm::vec3(0.f);
    direction_ = glm::vec3(0.f);
}
