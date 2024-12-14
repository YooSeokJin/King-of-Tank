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
	std::shared_ptr<Mesh>& getGun() { return meshes_[4]; }
	glm::vec3 getTurretForward() const;
	float getTurretYaw() { return meshes_[2]->localTransform_.getYaw(); }
	glm::vec3 getFirePosition() const;
	void gunUpDown(int deltaY);

private:
	void moveTank();
	void rotateTurret();
	void checkState();
private:
	bool isForward_;
	bool isBackward_;

	float yawTarget_;
	float yawDiff_;

	float pitchTarget_;
	float pitchDiff_;

	float turretSpeed_;
	float gunSpeed_;
};

