#ifndef VIEWING_H
#define VIEWING_H
#include "glm/glm.hpp"

class Viewing {
public:
    Viewing(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 cameraAt = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f));
    ~Viewing();

    // 뷰 행렬 반환
    glm::mat4 getViewMatrix() const;

    // 카메라 상태 설정
    void setCameraPosition(const glm::vec3& position);
    void setCameraTarget(const glm::vec3& target);
    void setCameraUp(const glm::vec3& up);

private:
    glm::vec3 cameraPos; // 카메라 위치
    glm::vec3 cameraAt;  // 카메라가 바라보는 목표
    glm::vec3 cameraUp;  // 월드의 "위" 벡터
};
#endif

