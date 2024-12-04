#pragma once
#include "Object.h"
class EnermyZen {
public:
	EnermyZen() = delete;
	EnermyZen(std::vector<std::shared_ptr<Object>>& objs);

	void SpawnEnermy();
private:
	std::vector<std::shared_ptr<Object>>& objects_;
	glm::vec3 spawnPoint_;
};

class Enermy : public Object
{
public:
	Enermy();
	void update(float frameTime) override;
	void checkState();
	bool meshIndex_[6];
};

// 에너미
// 베이스가 충돌되면 모두 해제
// 하나씩 분리하는 재미를 주는건 어떨까.