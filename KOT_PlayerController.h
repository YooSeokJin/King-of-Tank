#pragma once
#include "PlayerController.h"
#include "BulletManager.h"
class Tank;
class KOT_PlayerController : public PlayerController
{
public:
	KOT_PlayerController();
	~KOT_PlayerController();
	void update(float frameTime) override;
	void event(unsigned char key, int x, int y) override;
	void keyDown(unsigned char key, int x, int y) override;
	void keyUp(unsigned char key, int x, int y) override;
	void mouseMotion(int x, int y) override;
	void mouseWheel(int button, int dir, int x, int y) override;
	void mouseInput(int button, int state, int x, int y) override;

	void setTankCamera();

	BulletManager* bulletManager_;
	std::shared_ptr<Tank> tank;
private:
	void attack();
private:
	bool isW_, isS_;
	bool isA_, isD_;

	float attackTime_;
};

