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

	// �ͷ� ȸ���� ���
	float yawTarget_;
	float yawDiff_ =0.f;
	// ��ž ȸ���� ���
	float targetPitch_;

	float turretSpeed_;
};

