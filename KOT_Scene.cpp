#include "KOT_Scene.h"
#include "Tank.h"
#include "global.h"
#include "KOT_PlayerController.h"
KOT_Scene::KOT_Scene()
{
	backgroundColor_ = colorPaletteV4_[39];
	std::shared_ptr<Object> crane = std::make_shared<Tank>();
	objects_.push_back(crane);

	playeController_ = std::make_shared<KOT_PlayerController>();

	addCube(true); // ¹Ù´Ú
	staticObjects_[0]->setScale(50.f, 0.1f, 50.f);
	staticObjects_[0]->addPosition(0.f, -0.1f, 0.f);

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

	addLightCube(true); // ±¤¿ø »ý¼º
	staticObjects_[5]->setScale(0.2f, 0.2f, 0.2f);
	staticObjects_[5]->addPosition(objects_[0]->getPosition().x + 1.0f, 
								objects_[0]->getPosition().y + 5.0f,
								objects_[0]->getPosition().z + 1.0f);

	Init();
	
	auto tpc = std::dynamic_pointer_cast<KOT_PlayerController>(playeController_);
	tpc->setTankCamera();
}

void KOT_Scene::timer(float delta)
{
	update(delta);
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
