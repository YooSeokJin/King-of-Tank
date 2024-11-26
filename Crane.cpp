#include "Crane.h"
#include "global.h"
#include "Grid.h"
import ObjectLoader;

Crane::Crane()
{
	addGrid();
	meshes = ObjectLoader::Load_Meshes("objs/tank.obj", "Model");
	// 0 - Base
	// 1 - Right Track
	// 2 - Turret
	// 3 - Gun
	// 4 - Gun Holder
	// 5 - Right Track
	meshes[0]->Color = new glm::vec4(colorPalette[27]);
	meshes[1]->Color = new glm::vec4(BlackColor);
	meshes[2]->Color = new glm::vec4(colorPalette[19]);
	meshes[3]->Color = new glm::vec4(colorPalette[11]);
	meshes[4]->Color = new glm::vec4(colorPalette[38]);
	meshes[5]->Color = new glm::vec4(BlackColor);
}

void Crane::update(float frameTime)
{	
	Object::update(frameTime);
}

void Crane::move_F()
{
	printf("F\n");
	move.add_direction(1.f, 0.f, 0.f);
}

void Crane::move_B()
{
	move.add_direction(-1.f, 0.f, 0.f);
}

void Crane::rt_Y()
{
	move.add_rt_direction(0.f, 1.f, 0.f);
}

void Crane::rt_Y_R()
{
	move.add_rt_direction(0.f, -1.f, 0.f);
}



