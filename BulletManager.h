#pragma once
#include "Bullet.h"
class BulletManager {
public:
	void newBullet(std::shared_ptr<Bullet> bullet);
	std::shared_ptr<Bullet> newBullets_;
};

