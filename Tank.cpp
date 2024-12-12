#include "Tank.h"
#include <math.h>
#include "global.h"
#include "Grid.h"

import ObjectLoader;

Tank::Tank()
{
	tag_ = 'P';
	meshes_ = ObjectLoader::M_loadMesh("objs/tank.obj", "Model");
	for (auto& mesh : meshes_) {
		mesh->localTransform_.rotateY(180.f);
	}

	yawTarget_ = pitchTarget_ = 0.f;
	turretSpeed_ = 1.f;
	gunSpeed_ = 0.1f;
	pitchDiff_ = yawDiff_ = 0.0f;
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

void Tank::setCamera(const Camera* camera)
{
	camera_ = camera;
}

glm::vec3 Tank::getTurretForward()
{
	return meshes_[2]->localTransform_.getForwardVector();
}

glm::vec3 Tank::getFirePosition()
{
	if (!meshes_[3]) return glm::vec3(0);
	auto& gun = meshes_[3];

	std::vector<float> aabb = gun->getAabb();
	float x = (aabb[0] + aabb[1]) / 2;
	float y = (aabb[2] + aabb[3]) / 2;
	float z = (aabb[4] + aabb[5]) / 2;

	return glm::vec3(x, y, z);
}
void Tank::gunUpDown(int deltaY)
{
	int d = (deltaY < 0 ? 1 : -1);
	if (deltaY == 0) d= 0;
	float pitch = meshes_[4]->localTransform_.getPitch() + (d * gunSpeed_);
	
	pitch = glm::clamp(pitch, -5.f, 5.f);
	for (int i = 3; i < 5; ++i)
		meshes_[i]->localTransform_.setRotationZ(pitch);
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
	yawDiff_ = yawTarget_ - meshes_[2]->localTransform_.getYaw();
	
	if (yawDiff_ > 180.0f) yawDiff_ -= 360.0f;
	if (yawDiff_ < -180.0f) yawDiff_ += 360.0f;

	float d = 0.f;
	if (yawDiff_ < 0) d = -1.0f;
	else d = 1.0f;

	if (-1.0f <= yawDiff_ && yawDiff_ <= 1.0f) 
		for (int i = 2; i < 5; ++i) 
			meshes_[i]->localTransform_.rotateY(-yawDiff_);
	
	else 
		for (int i = 2; i < 5; ++i) 
			meshes_[i]->localTransform_.rotateY(-d * turretSpeed_);

}

void Tank::checkState()
{
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



