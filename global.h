#pragma once

#include <random>
#include "glm/glm.hpp"
#include "stb_image.h"

struct BMPImage {
    unsigned char* data;
    unsigned int width;
    unsigned int height;
    ~BMPImage() { if (data) delete[] data; }
};

extern bool showCollision;

extern int width_;
extern int height_;
extern int windowCenterX_;
extern int windowCenterY_;
extern int miniMapWidth_;
extern int miniMapHeight_;

extern std::random_device randomEngine_;
extern std::mt19937 mt_;
extern std::uniform_real_distribution<float> ufd_;
extern std::uniform_int_distribution<int> uid_;

// 컬러 팔레트 (RGBA)
const extern glm::vec4 colorPaletteV4_[40];
const extern glm::vec4 blackColorV4_;
const extern glm::vec4 whiteColorV4_;

//void changeRandomSize(float min, float max);
extern void changeOpenGL(int x, int y, int z, glm::vec3& center);
extern void changeOpenGL(const glm::vec3& windowPoints, glm::vec3& myPoints);
extern glm::vec3 screenToWorld(float ndcX, float ndcY, const glm::mat4& view, const glm::mat4& proj);
