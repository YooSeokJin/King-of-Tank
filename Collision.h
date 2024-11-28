#pragma once
#include <vector>

class Collision {
public:
	Collision();
	void set_aabb(const std::vector<float>& aabb);
	std::vector<float> get_aabb() const;
protected:
	std::vector<float> aabb;
};