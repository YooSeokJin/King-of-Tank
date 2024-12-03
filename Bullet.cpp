#include "Bullet.h"
#include "global.h"
import ObjectLoader;

Bullet::Bullet(const glm::vec3& startPos, const glm::vec3& forwardVector, float yaw)
{
	movedist = 0.f;
	// �̵� ����
	worldTransform_.setLocation(startPos + forwardVector);
	movement_.setDirection(forwardVector);
	movement_.setVelocity(30.f, 1.f, 30.f);

	// �޽� ����
	meshes_ = ObjectLoader::M_loadMesh("./objs/rocket.obj", "Model");

	meshes_[0]->localTransform_.setScale(glm::vec3(0.2f, 0.2f, 0.2f));
	meshes_[0]->applyMovement();
	meshes_[0]->localTransform_.setRotationY(yaw);

	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[23]);
	meshes_[0]->addCollision();

	// �׻� �θ� ������ �޽� ������ ������
	meshes_[0]->setParent(&worldTransform_);

	isDel = false;
}

void Bullet::update(float frameTime)
{
	if (!collisionStates_.empty()) {
		movement_.setDirection(0.f, 0.f, 0.f);
	}
	glm::vec3 move = movement_.getDeltaPosition();
	movedist += glm::length(move);
	Object::update(frameTime);

	if (movedist >= 100.f) {
		isDel = true;
	}
}

