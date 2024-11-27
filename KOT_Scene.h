#pragma once
#include "Scene.h"
class KOT_Scene: public Scene
{
public:
	KOT_Scene();

	void timer(float delta) override;
	void event(unsigned char key, int x, int y) override;
};

