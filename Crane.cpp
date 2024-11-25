#include "Crane.h"
#include "global.h"
import ObjectLoader;

Crane::Crane()
{
	addGrid();
	meshes = ObjectLoader::Load_Meshes("objs/tank.obj", "Model");
	for (auto& mesh : meshes) {
		mesh->Local_Transform.setRotationY(90.f);
		mesh->apply_movement();
	}
	int Cindex = 0;
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
	size_t len = meshes.size();

	printf("%d\n", len);
}

void Crane::update(float frameTime)
{	
	Object::update(frameTime);
}
