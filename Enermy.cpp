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
		mesh->setParent(&worldTransform_);
	}
	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[1]->meshColor_ = new glm::vec4(blackColorV4_);
	meshes_[2]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[3]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[4]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[5]->meshColor_ = new glm::vec4(blackColorV4_);

	movement_.setVelocity(15.f, 10.f, 15.f);
}

void Enermy::update(float frameTime)
{
	checkState();
	Object::update(frameTime);
}

void Enermy::checkState()
{
	glm::vec3 dir = movement_.getDirection();
	if (collisionStates_.contains('B')); //printf("boom!\n");
	if (collisionStates_.contains('F')) {
		if (dir.y >= 0.f) movement_.setDirectionY(-1.f);
	}
	if (collisionStates_.contains('O')) {
		if (dir.y <= 0.f) movement_.setDirectionY(0.f);
	}
}
