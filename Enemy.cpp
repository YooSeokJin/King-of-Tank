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
	: targetDiff_(0.f)
{
	tag_ = 'E';
	behavior_ = 'N';

	meshes_ = ObjectLoader::M_loadMesh("objs/tank.obj", "Model");
	for (auto& mesh : meshes_) {
		mesh->applyMovement();
		mesh->addCollision();
		mesh->addMovement();
		mesh->setParent(&worldTransform_);
		float dx = float(uid_(mt_) % 10 + 1);
		float dy = float(uid_(mt_) % 15 + 5);
		float dz = float(uid_(mt_) % 10 + 1);
		mesh->movement_->setVelocity(dx, dy, dz);
		mesh->movement_->setRtVelocity(90.f, 0.f, 90.f);
	}
	meshes_[0]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[1]->meshColor_ = new glm::vec4(blackColorV4_);
	meshes_[2]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[3]->meshColor_ = new glm::vec4(blackColorV4_);
	meshes_[4]->meshColor_ = new glm::vec4(colorPaletteV4_[0]);
	meshes_[5]->meshColor_ = new glm::vec4(blackColorV4_);

	movement_.setVelocity(3.f, 10.f, 3.f);
	movement_.setRtVelocity(15.f, 20.f, 15.f);
	fallingSpeed_ = 1.f;
	deadTime_ = 3.f;
	angle_ = 0.f;
	dist_ = 0.f;
}

void Enemy::update(float frameTime)
{
	if (tag_ == 'L') return;
	else if (tag_ == 'H') explode(frameTime);
	else if (tag_ == 'M') arrangeMeshes(frameTime);
	else if (tag_ == 'D') dead(frameTime);
	else {
		checkBehavior();
		doAction();
		checkState();
	}

	Object::update(frameTime);
}

void Enemy::checkState()
{
	if (tag_ == 'N') return;
	glm::vec3 dir = movement_.getDirection();
	if (collisionStates_.contains('B')) {
		movement_.setDirection(0, 0, 0);
		movement_.setRtDirection(0, 0, 0);
		tag_ = 'H';
		rotateMeshes();
	}
	if (collisionStates_.contains('F')) 
		if (dir.y >= 0.f) movement_.setDirectionY(-1.f);
	
	if (collisionStates_.contains('O')) 
		if (dir.y < -0.01f) {
			movement_.setDirectionY(0.f);
		}

}

void Enemy::explode(float frameTime)
{
	movement_.setDirectionY(fallingSpeed_);
	fallingSpeed_ -= frameTime;

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
	if (behavior_ == 'R') rotateToTarget();
	else if (behavior_ == 'M') moveToTarget();
	else if (behavior_ == 'A') attackToTarget();
}

void Enemy::checkBehavior()
{
	if (!collisionStates_.contains('O')) return;
	
	glm::vec3 norm = glm::normalize(target_->getPosition() - getPosition());
	glm::vec3 forward = -getForwardvector();
	glm::vec3 diff = norm - forward;

	float dotProduct = glm::dot(forward, norm);
	angle_ = glm::degrees(acos(glm::clamp(dotProduct, -1.0f, 1.0f)));

	glm::vec3 crossProduct = glm::cross(forward, norm);
	if (crossProduct.y < 0) {
		angle_ = -angle_;
	}

	if (!(-1.f <= angle_ && angle_ <= 1.f)) {
		movement_.setDirection(0, 0, 0);
		behavior_ = 'R';
	}
	else {
		movement_.setRtDirectionY(0.f);
		targetDiff_ = target_->getPosition() - getPosition();
		dist_ = glm::length(targetDiff_);
		if (dist_ > 30.f) behavior_ = 'M';
		else behavior_ = 'A';
	}
}

void Enemy::rotateToTarget()
{
	if (angle_ < 0) movement_.setRtDirectionY(-1.f);
	else movement_.setRtDirectionY(1.f);
}

void Enemy::moveToTarget()
{
	movement_.setDirection(-getForwardvector());
}

void Enemy::attackToTarget()
{
	if (dist_ < 50.f) movement_.setDirection(getForwardvector());
	else movement_.setDirection(0, 0, 0);
}
