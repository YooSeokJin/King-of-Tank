#pragma once
#include <vector>

class Collision {
public:
	Collision();
	void set_aabb(const std::vector<float>& aabb);
	const std::vector<float>& get_aabb();
protected:
	std::vector<float> aabb;
};