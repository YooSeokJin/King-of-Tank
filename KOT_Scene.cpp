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
		mesh->textureType_ = 1;
		mesh->resolX_ = 64;
		mesh->resolY_ = 64;
	}
	addCube(true);
	staticObjects_[1]->setScale(0.1f, 5.f, 50.f);
	staticObjects_[1]->addPosition(50.f, 5.f, 0.f);
	for (auto& mesh : staticObjects_[1]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
		mesh->textureType_ = 2;
		mesh->resolX_ = 8;
		mesh->resolY_ = 40;
	}

	addCube(true);
	staticObjects_[2]->setScale(0.1f, 5.f, 50.f);
	staticObjects_[2]->addPosition(-50.f, 5.f, 0.f);
	for (auto& mesh : staticObjects_[2]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
		mesh->textureType_ = 2;
		mesh->resolX_ = 8;
		mesh->resolY_ = 40;
	}

	addCube(true);
	staticObjects_[3]->setScale(50.f, 5.f, 0.1f);
	staticObjects_[3]->addPosition(0.f, 5.f, 50.f);
	for (auto& mesh : staticObjects_[3]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
		mesh->textureType_ = 2;
		mesh->resolX_ = 8;
		mesh->resolY_ = 40;
	}

	addCube(true);
	staticObjects_[4]->setScale(50.f, 5.f, 0.1f);
	staticObjects_[4]->addPosition(0.f, 5.f, -50.f);
	for (auto& mesh : staticObjects_[4]->getMeshes()) {
		mesh->meshColor_ = new glm::vec4(whiteColorV4_);
		mesh->textureType_ = 2;
		mesh->resolX_ = 8;
		mesh->resolY_ = 40;
	} 

	//addLightCube(true);
	//staticObjects_[5]->setScale(0.2f, 0.2f, 0.2f);
	//staticObjects_[5]->addPosition(objects_[0]->getPosition().x + 0.f, 
	//							objects_[0]->getPosition().y + 1.0f,
	//							objects_[0]->getPosition().z + 0.f);
	//for (auto& mesh : staticObjects_[5]->getMeshes()) {
	//	mesh->meshColor_ = new glm::vec4(whiteColorV4_);
	//	mesh->meshColor_->w = 0.f;
	//}
	//backgroundColor_ = colorPaletteV4_[39];

	addTree();
	staticObjects_[5]->setScale(0.1f, 0.1f, 0.1f);
	staticObjects_[5]->setRotation(0, uid_(mt_) % 90, 0);
	staticObjects_[5]->addPosition(0.f, 0.f, 20.f + uid_(mt_) % 10);
	int index = 0;
	for (auto& mesh : staticObjects_[5]->getMeshes()) {
		if (index == 0)
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[3]);
		else {
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[13]);
		}
		++index;
	}
	addTree();
	staticObjects_[6]->setScale(0.1f, 0.1f, 0.1f);
	staticObjects_[6]->setRotation(0, uid_(mt_) % 90, 0);
	staticObjects_[6]->addPosition(0.f, 0.f, -20.f - uid_(mt_) % 10);
	index = 0;
	for (auto& mesh : staticObjects_[6]->getMeshes()) {
		if (index == 0)
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[3]);
		else {
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[13]);
		}
		++index;
	}
	addTree();
	staticObjects_[7]->setScale(0.1f, 0.1f, 0.1f);
	staticObjects_[7]->setRotation(0, uid_(mt_) % 90, 0);
	staticObjects_[7]->addPosition(20.f + uid_(mt_) % 10, 0.f, 0.f);
	index = 0;
	for (auto& mesh : staticObjects_[7]->getMeshes()) {
		if (index == 0)
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[3]);
		else {
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[13]);
		}
		++index;
	}

	addTree();
	staticObjects_[8]->setScale(0.1f, 0.1f, 0.1f);
	staticObjects_[8]->setRotation(0, uid_(mt_) % 90, 0);
	staticObjects_[8]->addPosition(-20.f - uid_(mt_) % 10, 0.f, 0.f);
	index = 0;
	for (auto& mesh : staticObjects_[8]->getMeshes()) {
		if (index == 0)
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[3]);
		else {
			mesh->meshColor_ = new glm::vec4(colorPaletteV4_[13]);
		}
		++index;
	}

	Init();
	
	auto tpc = std::dynamic_pointer_cast<KOT_PlayerController>(playeController_);
	tpc->setTankCamera();
	tpc->bulletManager_ = &bulletManager_;
	tpc->tank_ = std::dynamic_pointer_cast<Tank>(tank);

	aim_ = std::make_shared<Aim>();

	enemyZen_.bulletManager = &bulletManager_;
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
	bullet->setColor();
	Renderer::M_setupObject(bullet);
	bullets_.push_back(bullet);
}
