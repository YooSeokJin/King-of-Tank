#include "Movement.h"

Movement::Movement()
    : velocity(5.f), direction(0.f), delta_position(0.f),
    rotation_velocity(30.f), rotation_direction(0.f), delta_rotation(0.f)
{
}
void Movement::update(float frame_time)
{
    delta_position = direction * velocity * frame_time;
    delta_rotation = rotation_direction * rotation_velocity * frame_time;
}
void Movement::set_velocity(float vx, float vy, float vz)
{
    glm::vec3 v(vx, vy, vz);
    velocity = glm::vec3(v);
}
void Movement::set_rt_velocity(float vx, float vy, float vz)
{
    glm::vec3 v(vx, vy, vz);
    rotation_velocity = v;
}

void Movement::add_direction(float dx, float dy, float dz)
{
    glm::vec3 d(dx, dy, dz);
    direction += d;
}

void Movement::add_rt_direction(float dx, float dy, float dz)
{
    glm::vec3 rd(dx, dy, dz);
    rotation_direction += rd;
}

void Movement::set_direction(float dx, float dy, float dz)
{
    glm::vec3 d(dx, dy, dz);
    if (glm::length(d) > 0.0f) {
        direction = glm::normalize(d);
    }
    else {
        direction = glm::vec3(0.0f);
    }
}

void Movement::set_direction_X(float delta)
{
    direction.x = delta;
}

void Movement::set_direction_Y(float delta)
{
    direction.y = delta;
}

void Movement::set_direction_Z(float delta)
{
    direction.z = delta;
}

void Movement::set_rt_direction(float dx, float dy, float dz)
{
    glm::vec3 d(dx, dy, dz);
    if (glm::length(d) > 0.0f) {
        rotation_direction = glm::normalize(d);
    }
    else {
        rotation_direction = glm::vec3(0.0f);
    }
}

void Movement::set_rt_direction_X(float delta)
{
    rotation_direction.x = delta;
}

void Movement::set_rt_direction_Y(float delta)
{
    rotation_direction.y = delta;
}

void Movement::set_rt_direction_Z(float delta)
{
    rotation_direction.z = delta;
}

const glm::vec3& Movement::get_delta_position()
{
    return delta_position;
}

const glm::vec3& Movement::get_delta_rotation()
{
    return delta_rotation;
}
