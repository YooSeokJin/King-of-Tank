#include "Bullet.h"
#include "global.h"
import ObjectLoader;

Bullet::Bullet(const glm::vec3& startPos, const glm::vec3& forwardVector, float yaw)
{
	travelTime_ = 0.f;
	// 이동 관련
	worldTransform_.setLocation(startPos + forwardVector);
	movement_.setDirection(forwardVector);
	movement_.setVelocity(30.f, 1.f, 30.f);

	// 메시 관련
	meshes_ = ObjectLoader::M_loadMesh("./objs/rocket.obj", "Model");

	meshes_[0]->localTransform_.setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	meshes_[0]->applyMovement();
	meshes_[0]->localTransform_.setRotationY(yaw);

	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[23]);
	meshes_[0]->addCollision();

	// 항상 부모 설정은 메시 설정이 끝나고
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
}

void Bullet::checkState()
{
	if (collisionStates_.contains('O')) dontMove_ = true;

	if (dontMove_) {
		movement_.setDirection(0.f, 0.f, 0.f);
	}
}

void Bullet::checkTravel(float frameTime)
{
	travelTime_ += frameTime;

	if (travelTime_ >= 3.f) isDel = true;
}

