#pragma once
#include "Object.h"

class EnemyZen {
public:
	EnemyZen() = delete;
	EnemyZen(std::vector<std::shared_ptr<Object>>& objs);

	void SpawnEnermy(float frameTime);
	void setTarget(std::shared_ptr<Object>& target);
private:
	std::vector<std::shared_ptr<Object>>& objects_;
	glm::vec3 spawnPoint1_;
	glm::vec3 spawnPoint2_;
	glm::vec3 spawnPoint3_;
	glm::vec3 spawnPoint4_;

	float spawnTime_;
	int where_;

	std::shared_ptr<Object> target_;
};

class Enemy : public Object
{
public:
	Enemy();
	void update(float frameTime) override;
	void checkState();
	void explode(float frameTime);
	void setTarget(std::shared_ptr<Object> target);

private:
	void checkMeshes();
	bool checkMesh(std::shared_ptr<Mesh> mesh);
	void endFalling();
	void rotateMeshes();
	void arrangeMeshes(float frameTime);
	void dead(float frameTime);

	void doAction();
	float fallingSpeed_;
	float deadTime_;

	void checkBehavior();
	void rotateToTarget();
	void moveToTarget();
	void attackToTarget();

	std::shared_ptr<Object> target_;
	char behavior_;
	float angle_;
	glm::vec3 targetDiff_;
	float dist_;
};
