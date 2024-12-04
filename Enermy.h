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

// ���ʹ�
// ���̽��� �浹�Ǹ� ��� ����
// �ϳ��� �и��ϴ� ��̸� �ִ°� ���.