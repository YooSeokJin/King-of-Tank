#pragma once
#include "Object.h"
#include "Camera.h"
class Tank : public Object {
public:
	Tank();
	void update(float frameTime) override;

	void moveForward();
	void moveBackward();
	void rotateY();
	void rotateY_R();

	void setAngle(const glm::vec3& dir);
	void setCamera(const Camera* camera);
	const Camera* camera_ = nullptr;
private:
	void moveTank();
	void rotateTurret();
	void checkState();
private:
	bool isForward_;
	bool isBackward_;

	// 터렛 회전에 사용
	float yawTarget_;
	float yawDiff_ =0.f;
	// 포탑 회전에 사용
	float targetPitch_;

	float turretSpeed_;
};

