#include "Aim.h"

Aim::Aim()
{
	target_ = nullptr;
	isRed_ = true;
	isDirty_ = false;
	tag_ = 'A';
}

void Aim::update()
{
	startPosition_ = target_->getFirePosition() + target_->getTurretForward();
	endPosition_ = target_->getTurretForward();
	endPosition_ *= 5000;
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

void Aim::calculateEndPoint(const std::vector<std::shared_ptr<Object>>& enemy, 
	const std::vector<std::shared_ptr<Static_Object>>& walls)
{
	glm::vec3 dir = getDirection();
	for (const auto& e : enemy) {
		for (const auto& mesh : e->getMeshes()) {
			std::vector<float> aabb = mesh->getAabb();
		}
	}
}
