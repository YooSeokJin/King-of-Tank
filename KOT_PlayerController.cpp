#include "KOT_PlayerController.h"
#include "Tank.h"

KOT_PlayerController::KOT_PlayerController()
{
	camera_offset = glm::vec3(-15.f, 10.f, 0.f);
	w = s = false;
	a = d = false;

}

void KOT_PlayerController::event(unsigned char key, int x, int y)
{
}

void KOT_PlayerController::K_D(unsigned char key, int x, int y)
{
	auto crane = std::dynamic_pointer_cast<Tank>(target);
	if (key == 'w' && !w) {
		crane->move_F();
		w = !w;
	}
	else if (key == 's' && !s) {
		crane->move_B();
		s = !s;
	}
	else if (key == 'a' && !a) {
		crane->rt_Y();
		a = !a;
	}
	else if (key == 'd' && !d) {
		crane->rt_Y_R();
		d = !d;
	}
}

void KOT_PlayerController::K_U(unsigned char key, int x, int y)
{
	auto crane = std::dynamic_pointer_cast<Tank>(target);
	if (key == 'w' && w) {
		crane->move_F();
		w = !w;
	}
	else if (key == 's' && s) {

		crane->move_B();
		s = !s;
	}
	else if (key == 'a' && a) {
		crane->rt_Y_R();
		a = !a;
	}
	else if (key == 'd' && d) {
		crane->rt_Y();
		d = !d;
	}

}
