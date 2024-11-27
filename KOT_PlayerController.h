#pragma once
#include "PlayerController.h"

class KOT_PlayerController : public PlayerController
{
public:
	KOT_PlayerController();
	void event(unsigned char key, int x, int y) override;
	void K_D(unsigned char key, int x, int y) override;
	void K_U(unsigned char key, int x, int y) override;
private:
	bool w, s;
	bool a, d;
};
