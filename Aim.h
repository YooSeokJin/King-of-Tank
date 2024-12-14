#pragma once
#include "Tank.h"
#include "Line.h"
class Aim : public Line {
public:
	Aim();
	void update() override;
	void setTarget(std::shared_ptr<Tank> target);
	
	glm::vec3 getDirection() const;

private:
	const Tank* target_;
};