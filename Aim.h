#pragma once
#include "Tank.h"
#include "Line.h"
class Aim : public Line {
public:
	Aim();
	void update() override;
	void setTarget(std::shared_ptr<Tank> target);
	
	glm::vec3 getDirection() const;
	void calculateEndPoint(const std::vector<std::shared_ptr<Object>>& enemy,
		const std::vector<std::shared_ptr<Static_Object>>& walls);
private:

private:
	const Tank* target_;
	bool isRed_;

};