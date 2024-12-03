#pragma once
#include "Object.h"
class Bullet : public Object {
public:
	Bullet() = delete;
	Bullet(const glm::vec3& startPos, const glm::vec3& forwardVector, float yaw);
	~Bullet();
	void update(float frameTime) override;
	void checkState();
	void checkTravel(float frameTime);
	float travelTime_;
	bool dontMove_;
};
