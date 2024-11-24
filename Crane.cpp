#include "Crane.h"
#include "global.h"
import ObjectLoader;

Crane::Crane()
{
	addGrid();
	meshes = ObjectLoader::Load_Meshes("objs/tank.obj", "Model");
	int Cindex = 0;
	for (auto& mesh : meshes) {
		mesh->Color = new glm::vec4(colorPalette[Cindex]);
		++Cindex;
		mesh->show_all_vertex();
		mesh->add_movement();
		mesh->set_Pivot(0.f, 0.f, 0.f);
		mesh->Local_Transform.setRotationX(-90.f);
		mesh->Local_Transform.setRotationZ(90.f);
		mesh->apply_movement();
	}
	size_t len = meshes.size();

	printf("%d\n", len);
}

void Crane::update(float frameTime)
{	
	Object::update(frameTime);
}
