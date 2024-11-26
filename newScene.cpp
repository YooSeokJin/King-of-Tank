#include "newScene.h"
#include "Crane.h"
#include "global.h"
#include "newPlayerController.h"
newScene::newScene()
{
	bgColor = colorPalette[39];
	std::shared_ptr<Object> crane = std::make_shared<Crane>();
	objs.push_back(crane);

	pc = std::make_shared<newPlayerController>();
	
	add_Cube(true);
	static_objs[0]->setScale(10.f, 0.1f, 10.f);
	static_objs[0]->addPosition(0.f, -0.1f, 0.f);
	Init();
}

void newScene::timer(float delta)
{
	update(delta);
}

void newScene::event(unsigned char key, int x, int y)
{
	pc->event(key, x, y);
}
