#include "KOT_PlayerController.h"
#include "Tank.h"

KOT_PlayerController::KOT_PlayerController()
{
	cameraOffset_ = glm::vec3(-25.f, 0.f, 0.f);
	isW_ = isS_ = false;
	isA_ = isD_ = false;
	attackTime_ = 2.f;
	bulletManager_ = nullptr;
}

KOT_PlayerController::~KOT_PlayerController()
{
	bulletManager_ = nullptr;
}

void KOT_PlayerController::update(float frameTime)
{
	if (attackTime_ > 0.f) attackTime_ -= frameTime;
}

void KOT_PlayerController::event(unsigned char key, int x, int y)
{
}

void KOT_PlayerController::keyDown(unsigned char key, int x, int y)
{
	if (key == 'w' && !isW_) {
		tank_->moveForward();
		isW_ = !isW_;
	}
	else if (key == 's' && !isS_) {
		tank_->moveBackward();
		isS_ = !isS_;
	}
	else if (key == 'a' && !isA_) {
		tank_->rotateY();
		isA_ = !isA_;
	}
	else if (key == 'd' && !isD_) {
		tank_->rotateY_R();
		isD_ = !isD_;
	}
}

void KOT_PlayerController::keyUp(unsigned char key, int x, int y)
{
	if (key == 'w' && isW_) {
		tank_->moveForward();
		isW_ = !isW_;
	}
	else if (key == 's' && isS_) {
		tank_->moveBackward();
		isS_ = !isS_;
	}
	else if (key == 'a' && isA_) {
		tank_->rotateY_R();
		isA_ = !isA_;
	}
	else if (key == 'd' && isD_) {
		tank_->rotateY();
		isD_ = !isD_;
	}
}

void KOT_PlayerController::mouseMotion(int x, int y)
{
	camera_->rotate(x, y);
	tank_->gunUpDown(y);
}

void KOT_PlayerController::mouseWheel(int button, int dir, int x, int y)
{
	camera_->adjustFov(-dir * 0.5f);
}

void KOT_PlayerController::mouseInput(int button, int state, int x, int y)
{
	if (button == 0) {
		if (state == 0) {
			attack();
		}
	}
}

void KOT_PlayerController::setTankCamera()
{
	auto tank = std::dynamic_pointer_cast<Tank>(target_);
	tank->setCamera(camera_);
}

void KOT_PlayerController::attack()
{
	if (!bulletManager_) {
		printf("Check Bullet Manager\n");
		return;
	}
	if (attackTime_ > 0.f) return;
	const std::shared_ptr<Mesh> gun = tank_->getGun();
	glm::vec3 sp = tank_->getFirePosition();
	glm::vec3 fv = tank_->getTurretForward();
	float yaw = gun->localTransform_.getYaw();

	std::shared_ptr<Bullet> newBullet = 
		std::make_shared<Bullet>(sp, fv, yaw);
	newBullet->tag_ = 'P';
	bulletManager_->newBullets_ = newBullet;
	attackTime_ = 1.f;
	printf("Attack\n");
}

