#pragma once
#include "Scene.h"
class newScene : public Scene
{
public:
	newScene();

	void timer(float delta) override;
	void event(unsigned char key, int x, int y) override;
};

