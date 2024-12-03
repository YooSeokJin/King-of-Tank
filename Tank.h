#pragma once
#include "BulletManager.h"
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

	void setCamera(const Camera* camera);
	const Camera* camera_ = nullptr;

	std::shared_ptr<Mesh>& getTurret() { return meshes_[2]; }
	glm::vec3 getTurretForward();
	float getTurretYaw() { return meshes_[2]->localTransform_.getYaw(); }
	glm::vec3 getFirePosition();

	
private:
	void moveTank();
	void rotateTurret();
	void checkState();
private:
	bool isForward_;
	bool isBackward_;

	// �ͷ� ȸ���� ���
	float yawTarget_;
	float yawDiff_;
	// ��ž ȸ���� ���
	float targetPitch_;

	float turretSpeed_;
};

