#pragma once
#include "Object.h"
class EnemyZen {
public:
	EnemyZen() = delete;
	EnemyZen(std::vector<std::shared_ptr<Object>>& objs);

	void SpawnEnermy();
private:
	std::vector<std::shared_ptr<Object>>& objects_;
	glm::vec3 spawnPoint_;
};

class Enemy : public Object
{
public:
	Enemy();
	void update(float frameTime) override;
	void checkState();
	void exploded();
};

// ���ʹ�
// ���̽��� �浹�Ǹ� ��� ����
// �ϳ��� �и��ϴ� ��̸� �ִ°� ���.