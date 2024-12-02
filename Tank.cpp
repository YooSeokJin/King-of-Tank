#include "Tank.h"
#include <math.h>
#include "global.h"
#include "Grid.h"

import ObjectLoader;

Tank::Tank()
{
	addGrid();
	meshes_ = ObjectLoader::M_loadMesh("objs/tank.obj", "Model");
	for (auto& mesh : meshes_) {
		mesh->localTransform_.rotateY(180.f);
	}

	yawTarget_ = targetPitch_ = 0.f;
	turretSpeed_ = 0.01f;
	yawDiff_ = 0.0f;
	// 0 - Base
	// 1 - Right Track
	// 2 - Turret
	// 3 - Gun
	// 4 - Gun Holder
	// 5 - Right Track
	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[27]);
	meshes_[1]->meshColor_ = new glm::vec4(blackColorV4_);
	meshes_[2]->meshColor_ = new glm::vec4(colorPaletteV4_[19]);
	meshes_[3]->meshColor_ = new glm::vec4(colorPaletteV4_[11]);
	meshes_[4]->meshColor_ = new glm::vec4(colorPaletteV4_[38]);
	meshes_[5]->meshColor_ = new glm::vec4(blackColorV4_);

	isBackward_ = isForward_ = false;

	worldTransform_.moveLocationY(5.f);
}

void Tank::update(float frameTime)
{
	moveTank();
	rotateTurret();
	checkState();
	Object::update(frameTime);
}

void Tank::moveForward()
{
	isForward_ = !isForward_;
}

void Tank::moveBackward()
{
	isBackward_ = !isBackward_;
}

void Tank::rotateY()
{
	movement_.addRtDirection(0.f, 1.f, 0.f);
	for (int i = 2; i < 5; ++i) {
		meshes_[i]->movement_->addRtDirection(0.f, -1.f, 0.f);
	}
}

void Tank::rotateY_R()
{
	movement_.addRtDirection(0.f, -1.f, 0.f);
	for (int i = 2; i < 5; ++i) {
		meshes_[i]->movement_->addRtDirection(0.f, 1.f, 0.f);
	}
}

void Tank::setAngle(const glm::vec3& dir)
{

}

void Tank::setCamera(const Camera* camera)
{
	camera_ = camera;
}

void Tank::moveTank()
{
	glm::vec3 FVector(0.f);
	if (isForward_) FVector += worldTransform_.getForwardVector();
	if (isBackward_) FVector -= worldTransform_.getForwardVector();
	movement_.setDirection(FVector.x, FVector.y, FVector.z);
}

void Tank::rotateTurret()
{
	glm::vec3 dir = camera_->getForwardVector();
	yawTarget_ = glm::degrees(atan2(dir.z, dir.x));
	//to_pitch = glm::degrees(asin(dir.y)); 주포 위 아래 회전
	float t_yaw = meshes_[2]->localTransform_.getYaw();
	yawDiff_ = yawTarget_ - t_yaw;
	if (yawDiff_ > 180.0f) yawDiff_ -= 360.0f;
	if (yawDiff_ < -180.0f) yawDiff_ += 360.0f;
	if (-1.0f <= yawDiff_ && yawDiff_ <= 1.0f) {
		for (int i = 2; i < 5; ++i) {
			meshes_[i]->localTransform_.rotateY(-yawDiff_);
		}
	}
	else {
		for (int i = 2; i < 5; ++i) {
			meshes_[i]->localTransform_.rotateY(-yawDiff_ * turretSpeed_);
		}
	}
}

void Tank::checkState()
{
	bool p = false;
	for (char t : collisionStates_) {
		printf("%c, ", t);
		p = true;
	}
	if (p) printf("\n");
	glm::vec3 dir = movement_.getDirection();
	if (collisionStates_.contains('x')) {
		if (dir.x < 0.f) movement_.setDirectionX(0.f);
	}
	if (collisionStates_.contains('X')) {
		if (dir.x > 0.f) movement_.setDirectionX(0.f);
	}
	if (collisionStates_.contains('z')) {
		if (dir.z < 0.f) movement_.setDirectionZ(0.f);
	}
	if (collisionStates_.contains('Z')) {
		if (dir.z > 0.f) movement_.setDirectionZ(0.f);
	}
	if (collisionStates_.contains('F')) {
		if (dir.y >= 0.f) movement_.setDirectionY(-0.1f);
	}
	if (collisionStates_.contains('O')) {
		if (dir.y <= 0.f) movement_.setDirectionY(0.f);
	}
}



