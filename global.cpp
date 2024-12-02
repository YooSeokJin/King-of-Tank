#include "global.h"

bool showCollision = false;

int width_ = 1024;
int height_ = 1024;
int windowCenterX_ = width_ / 2;
int windowCenterY_ = height_ / 2;
std::random_device randomEngine_{ };
std::mt19937 mt_(randomEngine_());
std::uniform_real_distribution<float> ufd_{ };
std::uniform_int_distribution<int> uid_{ };

// 컬러 팔레트 (RGBA)
const glm::vec4 colorPaletteV4_[40] = {
    glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),    // 빨강 0
    glm::vec4(1.0f, 0.5f, 0.0f, 1.0f),    // 주황 1
    glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),    // 노랑 2
    glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),    // 초록 3
    glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),    // 파랑 4
    glm::vec4(0.29f, 0.0f, 0.51f, 1.0f),  // 남색 5
    glm::vec4(0.58f, 0.0f, 0.83f, 1.0f),  // 보라 6
    glm::vec4(1.0f, 0.75f, 0.8f, 1.0f),   // 핑크 7
    glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),    // 회색 8
    glm::vec4(1.0f, 0.4f, 0.7f, 1.0f),    // 밝은 핑크 9
    glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),    // 시안 10
    glm::vec4(0.0f, 0.5f, 0.5f, 1.0f),    // 어두운 시안 11
    glm::vec4(0.5f, 0.0f, 0.5f, 1.0f),    // 자주색 12
    glm::vec4(0.6f, 0.4f, 0.2f, 1.0f),    // 갈색 13
    glm::vec4(1.0f, 0.84f, 0.0f, 1.0f),   // 금색 14
    glm::vec4(0.93f, 0.91f, 0.67f, 1.0f), // 밝은 황색 15
    glm::vec4(0.1f, 0.1f, 0.44f, 1.0f),   // 다크블루 16
    glm::vec4(0.68f, 1.0f, 0.18f, 1.0f),  // 라임그린 17
    glm::vec4(0.95f, 0.64f, 0.37f, 1.0f), // 샐몬 18
    glm::vec4(0.47f, 0.53f, 0.6f, 1.0f),  // 슬레이트 그레이 19
    glm::vec4(0.25f, 0.88f, 0.82f, 1.0f), // 터쿼이즈 20
    glm::vec4(0.75f, 0.75f, 0.75f, 1.0f), // 은색 21
    glm::vec4(0.93f, 0.51f, 0.93f, 1.0f), // 바이올렛 22
    glm::vec4(1.0f, 0.08f, 0.58f, 1.0f),  // 핫핑크 23
    glm::vec4(0.6f, 0.2f, 0.8f, 1.0f),    // 다크 바이올렛 24
    glm::vec4(0.8f, 0.36f, 0.36f, 1.0f),  // 인디안 레드 25
    glm::vec4(0.98f, 0.5f, 0.45f, 1.0f),  // 코랄 26
    glm::vec4(0.13f, 0.55f, 0.13f, 1.0f), // 포레스트 그린 27
    glm::vec4(0.0f, 0.98f, 0.6f, 1.0f),   // 스프링 그린 28
    glm::vec4(0.86f, 0.44f, 0.58f, 1.0f), // 미디엄 바이올렛 레드 29
    glm::vec4(0.78f, 0.08f, 0.52f, 1.0f), // 딥 핑크 30
    glm::vec4(0.54f, 0.17f, 0.89f, 1.0f), // 미디엄 퍼플 31
    glm::vec4(0.72f, 0.45f, 0.2f, 1.0f),  // 샌디 브라운 32
    glm::vec4(0.82f, 0.41f, 0.12f, 1.0f), // 초콜릿 33
    glm::vec4(0.94f, 0.9f, 0.55f, 1.0f),  // 라이트 골든로드 34
    glm::vec4(0.98f, 0.92f, 0.84f, 1.0f), // 라이트 코랄 35
    glm::vec4(0.65f, 0.64f, 0.6f, 1.0f),  // 카리브해 블루 36
    glm::vec4(0.68f, 0.85f, 0.9f, 1.0f),  // 라이트 시안 37
    glm::vec4(0.56f, 0.73f, 0.56f, 1.0f), // 라이트 그린 38
    glm::vec4(0.5f, 0.5f, 1.0f, 1.0f),     // 라이트 블루 39
};
const glm::vec4 blackColorV4_(0.0f, 0.0f, 0.0f, 1.0f);
const glm::vec4 whiteColorV4_(1.0f, 1.0f, 1.0f, 1.0f);

void changeOpenGL(int x, int y, int z, glm::vec3& center)
{
    center.x = (static_cast<float>(x) / width_) * 2.0f - 1.0f;
	center.y = 1.0f - ((static_cast<float>(y) / height_) * 2.0f);
    center.z = static_cast<float>(z);
}

void changeOpenGL(const glm::vec3& windowPoints, glm::vec3& myPoints)
{
	myPoints.x = windowPoints.x / width_ * 2.0f - 1.0f;
	myPoints.y = 1.0f - windowPoints.y / height_ * 2.0f;
}

glm::vec3 screenToWorld(float ndcX, float ndcY, const glm::mat4& view, const glm::mat4& proj)
{
    glm::vec4 clipCoords(ndcX, ndcY, -1.0f, 1.0f);

    glm::vec4 screen = glm::inverse(proj) * clipCoords;
    screen.z = -1.f;
    screen.w = 0.f;

    glm::vec4 world = glm::inverse(view) * screen;
    
    return world;
}

float Change_X(int x)
{

    return (static_cast<float>(x) / width_) * 2.0f - 1.0f;
}

float Change_Y(int y)
{
    return 1.0f - ((static_cast<float>(y) / height_) * 2.0f);
}

