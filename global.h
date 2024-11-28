#ifndef GLOBAL_H
#define GLOBAL_H

#include <random>
#include "glm/glm.hpp"

extern bool showCollision;

extern int WinSizeX;
extern int WinSizeY;
extern int centerX;
extern int centerY;

extern std::random_device rd;
extern std::mt19937 mt;
extern std::uniform_real_distribution<float> ufd;
extern std::uniform_int_distribution<int> uid;

// 컬러 팔레트 (RGBA)
const extern glm::vec4 colorPalette[40];
const extern glm::vec4 BlackColor;
const extern glm::vec4 WhiteColor;

//void changeRandomSize(float min, float max);
extern void changeOpenGL(int x, int y, int z, glm::vec3& center);
extern void changeOpenGL(const glm::vec3& windowPoints, glm::vec3& myPoints);
extern glm::vec3 screenToWorld(float ndcX, float ndcY, const glm::mat4& view, const glm::mat4& proj);
#endif // !GLOBAL_H