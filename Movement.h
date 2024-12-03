#pragma once
#include <glm/glm.hpp>
class Movement {
public:
    Movement();

    void update(float frameTime);

    void setVelocity(float vx, float vy, float vz);
    void setRtVelocity(float vx, float vy, float vz);

    const glm::vec3& getDirection() const { return direction_; }
    const glm::vec3& getVelocity() const { return velocity_; } 
    
    void addDirection(float dx, float dy, float dz);
    void addRtDirection(float dx, float dy, float dz);

    void setDirection(const glm::vec3& dir);
    void setDirection(float dx, float dy, float dz);
    void setDirectionX(float delta);
    void setDirectionY(float delta);
    void setDirectionZ(float delta);

    void setRtDirection(float dx, float dy, float dz);
    void setRtDirectionX(float delta);
    void setRtDirectionY(float delta);
    void setRtDirectionZ(float delta);
    
    const glm::vec3& getDeltaPosition();
    const glm::vec3& getDeltaPosition(float dx, float dz);
    const glm::vec3& getDeltaRotation();

    void stop();
private:
    // 이동
    glm::vec3 direction_;
    glm::vec3 velocity_;
    glm::vec3 deltaPosition_;

    // 회전
    glm::vec3 rotationDirection_;
    glm::vec3 rotationVelocity_;
    glm::vec3 deltaRotation_;

    float fallingSpeed = 9.8f;
};