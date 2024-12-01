#include "KOT_PlayerController.h"
#include "Tank.h"

KOT_PlayerController::KOT_PlayerController()
{
	cameraOffset_ = glm::vec3(-25.f, 0.f, 0.f);
	isW_ = isS_ = false;
	isA_ = isD_ = false;
}

void KOT_PlayerController::event(unsigned char key, int x, int y)
{
}

void KOT_PlayerController::keyDown(unsigned char key, int x, int y)
{
	
	if (key == 'w' && !isW_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->moveForward();
		isW_ = !isW_;
	}
	else if (key == 's' && !isS_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->moveBackward();
		isS_ = !isS_;
	}
	else if (key == 'a' && !isA_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->rotateY();
		isA_ = !isA_;
	}
	else if (key == 'd' && !isD_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->rotateY_R();
		isD_ = !isD_;
	}
}

void KOT_PlayerController::keyUp(unsigned char key, int x, int y)
{
	if (key == 'w' && isW_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->moveForward();
		isW_ = !isW_;
	}
	else if (key == 's' && isS_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->moveBackward();
		isS_ = !isS_;
	}
	else if (key == 'a' && isA_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->rotateY_R();
		isA_ = !isA_;
	}
	else if (key == 'd' && isD_) {
		auto tank = std::dynamic_pointer_cast<Tank>(target_);
		tank->rotateY();
		isD_ = !isD_;
	}
}

void KOT_PlayerController::mouseMotion(int x, int y)
{
	camera_->rotate(x, y);
	glm::vec3 fV = camera_->getForwardVector();
}

void KOT_PlayerController::mouseWheel(int button, int dir, int x, int y)
{
	camera_->adjustFov(-dir * 0.5f);
}

void KOT_PlayerController::setTankCamera()
{
	auto tank = std::dynamic_pointer_cast<Tank>(target_);
	tank->setCamera(camera_);
}


