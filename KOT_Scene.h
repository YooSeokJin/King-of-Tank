#pragma once
#include "Scene.h"
#include "BulletManager.h"
#include "Enemy.h"

class KOT_Scene: public Scene
{
public:
	KOT_Scene();

	void timer(float delta) override;
	void event(unsigned char key, int x, int y) override;
	void mouseMotion(int x, int y) override;
	void update(float frameTime) override;

private:
	void checkBullet();
	void createBullet(std::shared_ptr<Bullet> bullet);
private:
	BulletManager bulletManager_;
	EnemyZen enemyZen;
};
