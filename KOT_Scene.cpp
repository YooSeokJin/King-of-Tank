#include "KOT_Scene.h"
#include "Tank.h"
#include "global.h"
#include "KOT_PlayerController.h"

import Renderer;
KOT_Scene::KOT_Scene()
	:enemyZen_ (objects_)
{
	backgroundColor_ = colorPaletteV4_[39];
	std::shared_ptr<Object> tank = std::make_shared<Tank>();
	objects_.push_back(tank);
	enemyZen_.setTarget(tank);
	playeController_ = std::make_shared<KOT_PlayerController>();
	
	addCube(true);
	staticObjects_[0]->setScale(50.f, 0.1f, 50.f);
	staticObjects_[0]->addPosition(0.f, -0.1f, 0.f);
	for (auto& mesh : staticObjects_[0]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(colorPaletteV4_[24]);
	}
	addCube(true);
	staticObjects_[1]->setScale(0.1f, 5.f, 50.f);
	staticObjects_[1]->addPosition(50.f, 5.f, 0.f);
	for (auto& mesh : staticObjects_[1]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
	}

	addCube(true);
	staticObjects_[2]->setScale(0.1f, 5.f, 50.f);
	staticObjects_[2]->addPosition(-50.f, 5.f, 0.f);
	for (auto& mesh : staticObjects_[2]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
	}

	addCube(true);
	staticObjects_[3]->setScale(50.f, 5.f, 0.1f);
	staticObjects_[3]->addPosition(0.f, 5.f, 50.f);
	for (auto& mesh : staticObjects_[3]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
	}

	addCube(true);
	staticObjects_[4]->setScale(50.f, 5.f, 0.1f);
	staticObjects_[4]->addPosition(0.f, 5.f, -50.f);
	for (auto& mesh : staticObjects_[4]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
	} 

	addLightCube(true);
	staticObjects_[5]->setScale(0.2f, 0.2f, 0.2f);
	staticObjects_[5]->addPosition(objects_[0]->getPosition().x + 0.f, 
								objects_[0]->getPosition().y + 1.0f,
								objects_[0]->getPosition().z + 0.f);
	for (auto& mesh : staticObjects_[5]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
		mesh->meshColor_->w = 0.f;
	}
	backgroundColor_ = colorPaletteV4_[39];

	Init();
	
	auto tpc = std::dynamic_pointer_cast<KOT_PlayerController>(playeController_);
	tpc->setTankCamera();
	tpc->bulletManager_ = &bulletManager_;
	tpc->tank_ = std::dynamic_pointer_cast<Tank>(tank);

	aim_ = std::make_shared<Aim>();

	aim_->setTarget(std::dynamic_pointer_cast<Tank>(tank));
	aim_->setUp();
	lines_.push_back(aim_);
}

void KOT_Scene::timer(float delta)
{
	update(delta);
	enemyZen_.SpawnEnermy(delta);
}

void KOT_Scene::event(unsigned char key, int x, int y)
{
	playeController_->event(key, x, y);
}

void KOT_Scene::mouseMotion(int x, int y)
{
	int deltaX = x - windowCenterX_;
	int deltaY = y - windowCenterY_;
	if (deltaX != 0 || deltaY != 0)
		playeController_->mouseMotion(deltaX, deltaY);
}

void KOT_Scene::update(float frameTime)
{
	checkBullet();
	Scene::update(frameTime);
}

void KOT_Scene::checkBullet()
{
	if (!bulletManager_.newBullets_) return;
	createBullet(bulletManager_.newBullets_);
	bulletManager_.newBullets_.reset();
}

void KOT_Scene::createBullet(std::shared_ptr<Bullet> bullet)
{
	Renderer::M_setupObject(bullet);
	bullets_.push_back(bullet);
}
