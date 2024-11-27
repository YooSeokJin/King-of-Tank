#pragma once
#include "Scene.h"
class KOF_Scene: public Scene
{
public:
	KOF_Scene();

	void timer(float delta) override;
	void event(unsigned char key, int x, int y) override;
};

