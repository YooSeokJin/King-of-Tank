#include "Bullet.h"
#include "global.h"
import ObjectLoader;

Bullet::Bullet(const glm::vec3& startPos, const glm::vec3& forwardVector, float yaw)
{
	travelTime_ = 0.f;
	// Movement
	worldTransform_.setLocation(startPos + forwardVector);
	movement_.setDirection(forwardVector);
	movement_.setVelocity(30.f, 30.f, 30.f);
	// MeshInfo
	meshes_ = ObjectLoader::M_loadMesh("./objs/rocket.obj", "Model");

	meshes_[0]->localTransform_.setScale(glm::vec3(0.25f, 0.25f, 0.25f));
	meshes_[0]->applyMovement();
	meshes_[0]->addCollision();
	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[14]);

	// Always setParent Last
	meshes_[0]->setParent(&worldTransform_);
	
	dontMove_ = false;
	changed_ = false;
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
	meshes_[0]->localTransform_.rotate(glm::vec3(15.f, 15.f, 15.f));
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
	if (collisionStates_.contains('I')) {
		if (!changed_)
			changeDir();
	}
}

void Bullet::checkTravel(float frameTime)
{
	travelTime_ += frameTime;

	if (travelTime_ >= 5.f) isDel_ = true;
}

void Bullet::changeDir()
{
	glm::vec3 dir = movement_.getDirection();
	dir.y += uid_(mt_) % 2 + 1;
	dir.z += uid_(mt_) % 2 - 1;
	dir.x += uid_(mt_) % 2 - 1;
	movement_.setDirection(dir);
	changed_ = true;
}

void Bullet::setColor()
{
	if (tag_ == 'P') meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[3]);
	else meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[10]);
}

