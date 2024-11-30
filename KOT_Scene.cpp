#include "KOT_Scene.h"
#include "Tank.h"
#include "global.h"
#include "KOT_PlayerController.h"
KOT_Scene::KOT_Scene()
{
	bgColor = colorPalette[39];
	std::shared_ptr<Object> crane = std::make_shared<Tank>();
	objs.push_back(crane);

	pc = std::make_shared<KOT_PlayerController>();

	add_Cube(true); // ¹Ù´Ú
	static_objs[0]->setScale(50.f, 0.1f, 50.f);
	static_objs[0]->addPosition(0.f, -0.1f, 0.f);

	add_Cube(true);
	static_objs[1]->setScale(0.1f, 5.f, 50.f);
	static_objs[1]->addPosition(50.f, 5.f, 0.f);
	for (auto& mesh : static_objs[1]->getMeshes()) {
		mesh->Color = new glm::vec4(WhiteColor);
	}

	add_Cube(true);
	static_objs[2]->setScale(0.1f, 5.f, 50.f);
	static_objs[2]->addPosition(-50.f, 5.f, 0.f);
	for (auto& mesh : static_objs[2]->getMeshes()) {
		mesh->Color = new glm::vec4(WhiteColor);
	}

	add_Cube(true);
	static_objs[3]->setScale(50.f, 5.f, 0.1f);
	static_objs[3]->addPosition(0.f, 5.f, 50.f);
	for (auto& mesh : static_objs[3]->getMeshes()) {
		mesh->Color = new glm::vec4(WhiteColor);
	}

	add_Cube(true);
	static_objs[4]->setScale(50.f, 5.f, 0.1f);
	static_objs[4]->addPosition(0.f, 5.f, -50.f);
	for (auto& mesh : static_objs[4]->getMeshes()) {
		mesh->Color = new glm::vec4(WhiteColor);
	} 

	add_LightCube(true); // ±¤¿ø »ý¼º
	static_objs[5]->setScale(0.2f, 0.2f, 0.2f);
	static_objs[5]->addPosition(objs[0]->getPosition().x + 2.0f, 
								objs[0]->getPosition().y + 2.0f,
								objs[0]->getPosition().z + 2.0f);

	Init();
	
	auto tpc = std::dynamic_pointer_cast<KOT_PlayerController>(pc);
	tpc->set_Tank_Camera();
}

void KOT_Scene::timer(float delta)
{
	update(delta);
}

void KOT_Scene::event(unsigned char key, int x, int y)
{
	pc->event(key, x, y);
}

void KOT_Scene::mouseMotion(int x, int y)
{
	int deltaX = x - centerX;
	int deltaY = y - centerY;
	if (deltaX != 0 || deltaY != 0)
		pc->mouseMotion(deltaX, deltaY);
}
