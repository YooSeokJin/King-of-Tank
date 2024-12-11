#include "Bullet.h"
#include "global.h"
import ObjectLoader;

Bullet::Bullet(const glm::vec3& startPos, const glm::vec3& forwardVector, float yaw)
{
	travelTime_ = 0.f;
	// Movement
	worldTransform_.setLocation(startPos + forwardVector);
	movement_.setDirection(forwardVector);
	movement_.setVelocity(30.f, 5.f, 30.f);
	dir_ = forwardVector; dir_ *= 10;
	// MeshInfo
	meshes_ = ObjectLoader::M_loadMesh("./objs/rocket.obj", "Model");

	meshes_[0]->localTransform_.setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	meshes_[0]->applyMovement();
	meshes_[0]->localTransform_.setRotationY(yaw);
	meshes_[0]->addCollision();
	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[14]);

	// Always setParent Last
	meshes_[0]->setParent(&worldTransform_);
	
	dontMove_ = false;
}

Bullet::~Bullet()
{
	printf("Del Bullet\n");
}

void Bullet::update(float frameTime)
{
	checkTravel(frameTime);
	if (dontMove_) return;
	checkState();
	Object::update(frameTime);
	meshes_[0]->localTransform_.rotate(dir_);
}
void Bullet::checkState()
{
	if (collisionStates_.contains('O')) dontMove_ = true;

	if (dontMove_) {
		movement_.setDirection(0.f, 0.f, 0.f);
	}
	if (collisionStates_.contains('b')) {
		movement_.setDirection(0.f, -1.f, 0.f);
	}
}

void Bullet::checkTravel(float frameTime)
{
	travelTime_ += frameTime;

	if (travelTime_ >= 5.f) isDel_ = true;
}

