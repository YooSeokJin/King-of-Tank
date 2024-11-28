#pragma once
#include "PlayerController.h"

class Tank;
class KOT_PlayerController : public PlayerController
{
public:
	KOT_PlayerController();
	void event(unsigned char key, int x, int y) override;
	void keyDown(unsigned char key, int x, int y) override;
	void keyUp(unsigned char key, int x, int y) override;
	void mouseMotion(int x, int y) override;
	void mouseWheel(int button, int dir, int x, int y) override;
private:
	bool w, s;
	bool a, d;
};

