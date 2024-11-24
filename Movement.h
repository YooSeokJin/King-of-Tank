#pragma once
#include <glm/glm.hpp>
class Movement {
public:
    Movement();

    void update(float frame_time);

    void set_velocity(float vx, float vy, float vz);
    void set_rt_velocity(float vx, float vy, float vz);
    const glm::vec3& get_direction() const { return direction; }
    const glm::vec3& get_velocity() const { return velocity; } 
    float get_velocity_X() const { return velocity.x; }
    void set_direction(float dx, float dy, float dz);
    void set_rt_direction(float dx, float dy, float dz);
    
    const glm::vec3& get_delta_position();
    const glm::vec3& get_delta_rotation();
private:
    // �̵�
    glm::vec3 direction;
    glm::vec3 velocity;
    glm::vec3 delta_position;

    // ȸ��
    glm::vec3 rotation_direction;
    glm::vec3 rotation_velocity;
    glm::vec3 delta_rotation;
};