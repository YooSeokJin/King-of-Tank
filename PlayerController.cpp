#include "PlayerController.h"

PlayerController::PlayerController()
{
	camera = nullptr;
	camera_offset = glm::vec3(-15.f, 5.f, 0.f);
}

PlayerController::PlayerController(std::shared_ptr<Object> target_)
{
	target = target_;
	camera = nullptr;
	camera_offset = glm::vec3(-10.f, 5.f, 0.f);
}

PlayerController::~PlayerController()
{
	camera = nullptr;
}

void PlayerController::event(unsigned char key, int x, int y)
{
}

void PlayerController::set_target(std::shared_ptr<Object> target_)
{
	if (!target) target = target_;
}

void PlayerController::set_camera(Camera* camera_)
{
	if (!camera) camera = camera_;
	if (!target) return;
	camera->followObject(target, camera_offset);
}