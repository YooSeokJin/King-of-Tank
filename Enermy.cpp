#include "Enermy.h"
#include "global.h"
import ObjectLoader;
import Renderer;
EnermyZen::EnermyZen(std::vector<std::shared_ptr<Object>>& objs)
	:objects_(objs)
{
	spawnPoint_ = glm::vec3(20.f, 20.f, 20.f);
}

void EnermyZen::SpawnEnermy()
{
	size_t objCount = objects_.size();
	if (objCount > 1) return;
	std::shared_ptr<Object> newEnermy = std::make_shared<Enermy>();
	newEnermy->setPosition(spawnPoint_);
	Renderer::M_setupObject(newEnermy);
	objects_.push_back(newEnermy);
	printf("ZenEnermy\n");
}

Enermy::Enermy()
{
	for (auto& b : meshIndex_) b = false;
	tag = 'E';

	meshes_ = ObjectLoader::M_loadMesh("objs/tank.obj", "Model");
	for (auto& mesh : meshes_) {
		mesh->applyMovement();
		mesh->addCollision();
		mesh->addMovement();
	}
	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[27]);
	meshes_[1]->meshColor_ = new glm::vec4(blackColorV4_);
	meshes_[2]->meshColor_ = new glm::vec4(colorPaletteV4_[19]);
	meshes_[3]->meshColor_ = new glm::vec4(colorPaletteV4_[11]);
	meshes_[4]->meshColor_ = new glm::vec4(colorPaletteV4_[38]);
	meshes_[5]->meshColor_ = new glm::vec4(blackColorV4_);
}

void Enermy::update(float frameTime)
{
	if (collisionStates_.contains('B')); //printf("boom!\n");

	for (int i = 0; i < 6; ++i) {
		if (meshIndex_[i]) printf("Collision %d\n", i);
	}
}