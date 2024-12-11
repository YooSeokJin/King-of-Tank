#include "Enemy.h"
#include "global.h"
import ObjectLoader;
import Renderer;
EnemyZen::EnemyZen(std::vector<std::shared_ptr<Object>>& objs)
	:objects_(objs)
{
	spawnPoint1_ = glm::vec3(40.f, 20.f, 0.f);
	spawnPoint2_ = glm::vec3(-40.f, 20.f, 0.f);
	spawnPoint3_ = glm::vec3(0.f, 20.f, -40.f);
	spawnPoint4_ = glm::vec3(0.f, 20.f, 40.f);
	spawnTime_ = 5.f;
	where_ = 0;
}

void EnemyZen::SpawnEnermy(float frameTime)
{
	if (objects_.size() > 4) return;
	spawnTime_ -= frameTime;
	if (spawnTime_ >= 0.f) return;

	std::shared_ptr<Object> newEnemy = std::make_shared<Enemy>();
	if (where_ == 0) newEnemy->setPosition(spawnPoint1_);
	else if (where_ == 1) newEnemy->setPosition(spawnPoint2_);
	else if (where_ == 2) newEnemy->setPosition(spawnPoint3_);
	else newEnemy->setPosition(spawnPoint4_);
	
	auto e = std::dynamic_pointer_cast<Enemy>(newEnemy);
	e->setTarget(target_);
	Renderer::M_setupObject(newEnemy);
	objects_.push_back(newEnemy);
	
	spawnTime_ = 5.f;
	where_ = (where_ + 1) % 4;
}

void EnemyZen::setTarget(std::shared_ptr<Object>& target)
{
	target_ = target;
}

Enemy::Enemy()
	:toTarget_(0.f)
{
	tag_ = 'E';
	behavior_ = 'N';

	meshes_ = ObjectLoader::M_loadMesh("objs/tank.obj", "Model");
	for (auto& mesh : meshes_) {
		mesh->applyMovement();
		mesh->addCollision();
		mesh->addMovement();
		mesh->setParent(&worldTransform_);
		mesh->movement_->setVelocity(6.f, 10.f, 6.f);
		mesh->movement_->setRtVelocity(180.f, 0.f, 180.f);
	}
	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[1]->meshColor_ = new glm::vec4(blackColorV4_);
	meshes_[2]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[3]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[4]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[5]->meshColor_ = new glm::vec4(blackColorV4_);

	movement_.setVelocity(15.f, 10.f, 15.f);

	fallingSpeed_ = 1.f;
	deadTime_ = 3.f;
}

void Enemy::update(float frameTime)
{
	if (tag_ == 'L') return;
	else if (tag_ == 'H') explode(frameTime);
	else if (tag_ == 'M') arrangeMeshes(frameTime);
	else if (tag_ == 'D') dead(frameTime);
	else if (tag_ == 'E') {
		checkState();
		doAction();
	}
	Object::update(frameTime);
}

void Enemy::checkState()
{
	if (tag_ == 'N') return;
	glm::vec3 dir = movement_.getDirection();
	if (collisionStates_.contains('B')) {
		tag_ = 'H';
		rotateMeshes();
	}
	if (collisionStates_.contains('F')) 
		if (dir.y >= 0.f)
			movement_.setDirectionY(-1.f);
	
	if (collisionStates_.contains('O')) 
		if (dir.y <= 0.f) {
			movement_.setDirectionY(0.f);
		}

	glm::vec3 toTarget = target_->getPosition() - getForwardvector();
}

void Enemy::explode(float frameTime)
{
	movement_.setDirectionY(fallingSpeed_);
	fallingSpeed_ -= frameTime;
	tag_ = 'H';

	checkMeshes();
}

void Enemy::setTarget(std::shared_ptr<Object> target)
{
	target_ = target;
}

void Enemy::checkMeshes()
{
	if (fallingSpeed_ >= 0.f) return;
	for (auto& mesh : getMeshes()) {
		if (checkMesh(mesh)) 
			endFalling();
	}
}

bool Enemy::checkMesh(std::shared_ptr<Mesh> mesh)
{
	std::vector<float> aabb = mesh->getAabb();
	if (aabb[1] <= 0.f || aabb[2] <= 0.f)
		return true;

	return false;
}

void Enemy::endFalling()
{
	movement_.setDirectionY(0);
	tag_ = 'M';
}

void Enemy::rotateMeshes()
{
	for (auto& mesh : getMeshes()) {
		int where = uid_(mt_) % 4;
		if (where == 0) {
			mesh->movement_->setRtDirectionX(1);
			mesh->movement_->setDirectionX(1);
		}
		else if (where == 1) {
			mesh->movement_->setRtDirectionX(-1);
			mesh->movement_->setDirectionX(-1);
		}
		else if (where == 2) {
			mesh->movement_->setRtDirectionZ(1);
			mesh->movement_->setDirectionZ(1);
		}
		else {
			mesh->movement_->setRtDirectionZ(-1);
			mesh->movement_->setDirectionZ(-1);
		}
	}
}

void Enemy::arrangeMeshes(float frameTime)
{
	bool allMeshesAligned = true;
	for (auto& mesh : meshes_) {
		glm::vec3 rt = mesh->localTransform_.getRotation();
		std::vector<float> aabb = mesh->getAabb();
		if (aabb[2] <= 0.f || aabb[3] <= 0.f) {
			mesh->movement_->setDirection(0, 0, 0);
			mesh->movement_->setRtDirection(0, 0, 0);
		}
		else {
			mesh->movement_->setDirectionY(-1.f);
			allMeshesAligned = false;
		}
	}
	if (allMeshesAligned) tag_ = 'D';
}

void Enemy::dead(float frameTime)
{
	deadTime_ -= frameTime;
	
	if (deadTime_ <= 0.f){
		tag_ = 'L';
		isDel_ = true;
	}
}

void Enemy::doAction()
{
	if (behavior_ == 'N') return;

	if (behavior_ == 'R') {
		rotateToTarget();

	}

	else if (behavior_ == 'M') {
		bool mv = moveToTarget();
		if (mv) attackToTarget();
	}

	else if (behavior_ == 'A') {
		attackToTarget();
	}
}

bool Enemy::rotateToTarget()
{
	float angle = atan2(toTarget_.z, toTarget_.x);
	float epsilon = 0.5f;
	if (angle < -epsilon) {
		movement_.setRtDirectionY(-1.f);
	}
	else if (angle > epsilon) {
		movement_.setRtDirectionY(1.f);
	}
	else {
		movement_.setRtDirectionY(0.f);
		return true;
	}
	return false;
}

bool Enemy::moveToTarget()
{
	return false;
}

bool Enemy::attackToTarget()
{
	return false;
}
