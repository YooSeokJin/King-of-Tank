#include "PlayerController.h"

PlayerController::PlayerController()
{
	camera_ = nullptr;
	cameraOffset_ = glm::vec3(-15.f, 5.f, 0.f);
}

PlayerController::PlayerController(std::shared_ptr<Object> target)
{
	target_ = target;
	camera_ = nullptr;
	cameraOffset_ = glm::vec3(10.f, 5.f, 0.f);
}

PlayerController::~PlayerController()
{
	camera_ = nullptr;
}

void PlayerController::event(unsigned char key, int x, int y)
{
}

void PlayerController::keyDown(unsigned char key, int x, int y)
{
}

void PlayerController::keyUp(unsigned char key, int x, int y)
{
}

void PlayerController::mouseMotion(int x, int y)
{
}

void PlayerController::mouseWheel(int button, int dir, int x, int y)
{
}

void PlayerController::setTarget(std::shared_ptr<Object> target)
{
	if (!target_) target_ = target;
}

void PlayerController::setCamera(Camera* camera)
{
	if (!camera_) camera_ = camera;
	if (!target_) return;
	camera_->followObject(target_, cameraOffset_);

}