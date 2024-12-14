#include "Aim.h"

Aim::Aim()
{
	target_ = nullptr;
	isDirty_ = false;
	tag_ = 'A';
}

void Aim::update()
{
	startPosition_ = target_->getFirePosition() + target_->getTurretForward();
	endPosition_ = target_->getTurretForward();
	endPosition_ *= 2500;
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);

	float vertices[6] = {
		startPosition_.x, startPosition_.y, startPosition_.z,
		endPosition_.x, endPosition_.y, endPosition_.z
	};

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Aim::setTarget(std::shared_ptr<Tank> target)
{
	target_ = target.get();
}

glm::vec3 Aim::getDirection() const
{
	return target_->getTurretForward();
}
