#pragma once
#include "Object.h"
class Bullet : public Object {
public:
	Bullet() = delete;
	Bullet(const glm::vec3& startPos, const glm::vec3& forwardVector, float yaw);

	void update(float frameTime) override;
	float movedist;
};
