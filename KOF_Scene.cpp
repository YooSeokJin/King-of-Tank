#include "KOF_Scene.h"
#include "Tank.h"
#include "global.h"
#include "KOF_PlayerController.h"
KOF_Scene::KOF_Scene()
{
	bgColor = colorPalette[39];
	std::shared_ptr<Object> crane = std::make_shared<Tank>();
	objs.push_back(crane);

	pc = std::make_shared<KOF_PlayerController>();

	add_Cube(true);
	static_objs[0]->setScale(10.f, 0.1f, 10.f);
	static_objs[0]->addPosition(0.f, -0.1f, 0.f);
	Init();
}

void KOF_Scene::timer(float delta)
{
	update(delta);
}

void KOF_Scene::event(unsigned char key, int x, int y)
{
	pc->event(key, x, y);
}
