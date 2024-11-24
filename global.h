#ifndef GLOBAL_H
#define GLOBAL_H

#include <random>
#include "glm/glm.hpp"

struct Color {
	float r, g, b, a;
	Color() {
		r = g = b = a = 0;
	}
	Color(float r_, float g_, float b_, float a_) {
		r = r_;
		g = g_;
		b = b_;
		a = a_;
	}
	Color(const Color& color) {
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	Color& operator=(const Color& color) {
		if (this != &color) {
			this->r = color.r;
			this->g = color.g;
			this->b = color.b;
			this->a = color.a;
		}
		return *this;
	}
};

extern int WinSizeX;
extern int WinSizeY;

extern std::random_device rd;
extern std::mt19937 mt;
extern std::uniform_real_distribution<float> ufd;
extern std::uniform_int_distribution<int> uid;

// 컬러 팔레트 (RGBA)
const extern glm::vec4 colorPalette[40];
const extern glm::vec4 BlackColor;
const extern glm::vec4 WhiteColor;

//void changeRandomSize(float min, float max);
void changeOpenGL(int x, int y, int z, glm::vec3& center);
void changeOpenGL(const glm::vec3& windowPoints, glm::vec3& myPoints);
#endif // !GLOBAL_H