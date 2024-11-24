#pragma once
#include <utility>

class Collsion {
public:
	Collsion();

protected:
	std::pair<float, float> minmax_X;
	std::pair<float, float> minmax_Y;
	std::pair<float, float> minmax_Z;
};