#include "KOT_PlayerController.h"
#include "Tank.h"

KOT_PlayerController::KOT_PlayerController()
{
	camera_offset = glm::vec3(-25.f, 0.f, 0.f);
	w = s = false;
	a = d = false;
}

void KOT_PlayerController::event(unsigned char key, int x, int y)
{
}

void KOT_PlayerController::keyDown(unsigned char key, int x, int y)
{
	
	if (key == 'w' && !w) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->move_F();
		w = !w;
	}
	else if (key == 's' && !s) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->move_B();
		s = !s;
	}
	else if (key == 'a' && !a) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->rt_Y();
		a = !a;
	}
	else if (key == 'd' && !d) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->rt_Y_R();
		d = !d;
	}
}

void KOT_PlayerController::keyUp(unsigned char key, int x, int y)
{
	if (key == 'w' && w) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->move_F();
		w = !w;
	}
	else if (key == 's' && s) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->move_B();
		s = !s;
	}
	else if (key == 'a' && a) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->rt_Y_R();
		a = !a;
	}
	else if (key == 'd' && d) {
		auto tank = std::dynamic_pointer_cast<Tank>(target);
		tank->rt_Y();
		d = !d;
	}
}

void KOT_PlayerController::mouseMotion(int x, int y)
{
	camera->rotate(x, y);
	float yaw = camera->getYaw();
	auto tank = std::dynamic_pointer_cast<Tank>(target);
	tank->rotate_turret(yaw);
}

void KOT_PlayerController::mouseWheel(int button, int dir, int x, int y)
{
	camera->adjustFov(-dir * 0.5f);
}


