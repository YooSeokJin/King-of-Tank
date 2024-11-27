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

	add_Cube(true);
	static_objs[0]->setScale(10.f, 0.1f, 10.f);
	static_objs[0]->addPosition(0.f, -0.1f, 0.f);
	Init();
}

void KOT_Scene::timer(float delta)
{
	update(delta);
}

void KOT_Scene::event(unsigned char key, int x, int y)
{
	pc->event(key, x, y);
}
