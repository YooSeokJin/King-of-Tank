#include "Object.h"
#include "Grid.h"

Object::Object()
{
	isDel_ = false;
	grid_ = nullptr;
}

Object::~Object()
{
	printf("Del Object\n");
	for (auto& mesh : meshes_) {
		mesh->deleteParent();
	}
	delete grid_;
}

void Object::drawGrid(const glm::mat4& view, const glm::mat4& proj)
{
	if (grid_) {
		glm::mat4 model = worldTransform_.getTransformMatrix();
		grid_->draw(view, proj, model);
	}
}

void Object::addGrid()
{
	if (!grid_) grid_ = new Grid();
}

void Object::update(float frameTime)
{
	movement_.update(frameTime);
	worldTransform_.moveLocation(movement_.getDeltaPosition());
	worldTransform_.rotate(movement_.getDeltaRotation());

	for (auto& mesh : meshes_) {
		mesh->update(frameTime);
	}
}

const std::vector<std::shared_ptr<Mesh>>& Object::getMeshes() const
{
	return meshes_;
}

void Object::addMesh(const std::shared_ptr<Mesh>& mesh)
{
	meshes_.push_back(mesh);
	mesh->applyMovement();
}

void Object::adjustDelta(float x, float y, float z)
{
	movement_.setDirection(x, y, z);
}

void Object::adjustDeltaX(float delta)
{
	movement_.setDirectionX(delta);
}

void Object::adjustDeltaY(float delta)
{
	movement_.setDirectionY(delta);
}

void Object::adjustDeltaZ(float delta)
{
	movement_.setDirectionZ(delta);
}

void Object::adjustRotate(float x, float y, float z)
{
	movement_.setRtDirection(x, y, z);
}

void Object::adjustRotateX(float delta)
{
	movement_.setRtDirectionX(delta);
}

void Object::adjustRotateY(float delta)
{
	movement_.setRtDirectionY(delta);
}

void Object::adjustRotateZ(float delta)
{
	movement_.setRtDirectionZ(delta);
}

void Object::setOrDeleteState(char type, bool isColliding)
{
	if (isColliding) {
		setObjectState(type);
	}
	else {
		deleteObjectState(type);
	}
}

void Object::setObjectState(char type)
{
	if (collisionStates_.contains(type)) return;
	collisionStates_.insert(type);
}

void Object::deleteObjectState(char type)
{
	if (!collisionStates_.contains(type)) return;
	collisionStates_.erase(type);
}

bool Object::isOnGround()
{
	return collisionStates_.contains('O');
}


// STATIC
Static_Object::Static_Object()
{
	tag_ = 'W';
}

void Static_Object::update(float frameTime)
{
	for (auto& mesh : meshes_) {
		mesh->update(frameTime);
	}
}

void Static_Object::Init()
{
	for (auto& mesh : meshes_) {
		mesh->setParent(&worldTransform_);
		mesh->init();
	}
}

const std::vector<std::shared_ptr<Mesh>>& Static_Object::getMeshes() const
{
	return meshes_;
}

void Static_Object::addMesh(const std::shared_ptr<Mesh>& mesh)
{
	meshes_.push_back(mesh);
}

void Static_Object::setScale(float x, float y, float z)
{
	worldTransform_.setScale(glm::vec3(x, y, z));
}

void Static_Object::setPosition(float x, float y, float z)
{
	worldTransform_.setLocation(glm::vec3(x, y, z));
}

void Static_Object::setPosition(const glm::vec3& position)
{
	worldTransform_.setLocation(position);
}

void Static_Object::setRotation(float x, float y, float z)
{
	worldTransform_.setRotation(glm::vec3(x, y, z));
}

void Static_Object::addScale(float x, float y, float z)
{
	worldTransform_.scale(glm::vec3(x, y, z));
}

void Static_Object::addPosition(float x, float y, float z)
{
	worldTransform_.moveLocation(glm::vec3(x, y, z));
}

void Static_Object::addRotation(float x, float y, float z)
{
	worldTransform_.rotate(glm::vec3(x, y, z));
}

