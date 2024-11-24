#ifndef VIEWING_H
#define VIEWING_H
#include "glm/glm.hpp"

class Viewing {
public:
    Viewing(glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 cameraAt = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f));
    ~Viewing();

    // �� ��� ��ȯ
    glm::mat4 getViewMatrix() const;

    // ī�޶� ���� ����
    void setCameraPosition(const glm::vec3& position);
    void setCameraTarget(const glm::vec3& target);
    void setCameraUp(const glm::vec3& up);

private:
    glm::vec3 cameraPos; // ī�޶� ��ġ
    glm::vec3 cameraAt;  // ī�޶� �ٶ󺸴� ��ǥ
    glm::vec3 cameraUp;  // ������ "��" ����
};
#endif

