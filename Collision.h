#pragma once
#include <vector>

class Collision {
public:
	Collision();
	void setAabb(const std::vector<float>& aabb);
	std::vector<float> getAabb() const;
protected:
	std::vector<float> aabb_;
};