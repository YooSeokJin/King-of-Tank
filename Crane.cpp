#include "Crane.h"
#include <math.h>
#include "global.h"
#include "Grid.h"

import ObjectLoader;

Crane::Crane()
{
	addGrid();
	meshes = ObjectLoader::Load_Meshes("objs/tank.obj", "Model");
	for (auto& mesh : meshes) {
		mesh->Local_Transform.rotateY(180.f);
	}
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

	Backward = Forward = false;
}

void Crane::update(float frameTime)
{	
	glm::vec3 FVector{ 0.f, 0.f, 0.f };
	if (Forward) {
		FVector += World_Transform.get_Forward_vector();
	}
	if (Backward) {
		FVector -= World_Transform.get_Forward_vector();
	}
	printf("%f, %f, %f\n", FVector.x, FVector.y, FVector.z);
	move.set_direction(FVector.x, FVector.y, FVector.z);
	Object::update(frameTime);
}

void Crane::move_F()
{	
	Forward = !Forward;
}

void Crane::move_B()
{
	Backward = !Backward;
}

void Crane::rt_Y()
{
	move.add_rt_direction(0.f, 1.f, 0.f);
}

void Crane::rt_Y_R()
{
	move.add_rt_direction(0.f, -1.f, 0.f);
}



