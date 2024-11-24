#include "Object.h"
#include "Grid.h"

Object::Object()
{
	grid = nullptr;
}

Object::~Object()
{
	for (auto& mesh : meshes) {
		mesh->delete_Parent();
	}
	delete grid;
}

void Object::DrawGrid(const glm::mat4& view, const glm::mat4& proj)
{
	if (grid) {
		glm::mat4 model = World_Transform.getTransformMatrix();
		grid->draw(view, proj, model);
	}
}

void Object::addGrid()
{
	if (!grid) grid = new Grid();
}

void Object::update(float frame_time)
{
	move.update(frame_time);
	World_Transform.translate(move.get_delta_position());
	World_Transform.rotate(move.get_delta_rotation());
	//glm::vec3 pos = World_Transform.getLocation();
	//printf("%f, %f, %f\n", pos.x, pos.y, pos.z);
	for (auto& mesh : meshes) {
		mesh->update(frame_time);
	}
}

const std::vector<std::shared_ptr<Mesh>>& Object::getMeshes() const
{
	return meshes;
}

void Object::addMesh(const std::shared_ptr<Mesh>& mesh)
{
	meshes.push_back(mesh);
	mesh->apply_movement();
	mesh->set_Parent(&World_Transform);
}

void Object::adjustDelta(float x, float y, float z)
{
	move.set_direction(x, y, z);
}

void Object::adjustRotate(float x, float y, float z)
{
	move.set_rt_direction(x, y, z);
}


Static_Object::Static_Object()
{
}

void Static_Object::update(float frameTime)
{
	for (auto& mesh : meshes) {
		mesh->update(frameTime);
	}
}

const std::vector<std::shared_ptr<Mesh>>& Static_Object::getMeshes() const
{
	return meshes;
}

void Static_Object::addMesh(const std::shared_ptr<Mesh>& mesh)
{
	meshes.push_back(mesh);
	mesh->set_Parent(&World_Transform);
}

void Static_Object::setScale(float x, float y, float z)
{
	World_Transform.setScale(glm::vec3(x, y, z));
}

void Static_Object::setPosition(float x, float y, float z)
{
	World_Transform.setLocation(glm::vec3(x, y, z));
}

void Static_Object::setRotation(float x, float y, float z)
{
	World_Transform.setRotation(glm::vec3(x, y, z));
}

void Static_Object::addScale(float x, float y, float z)
{
	World_Transform.scale(glm::vec3(x, y, z));
}

void Static_Object::addPosition(float x, float y, float z)
{
	World_Transform.translate(glm::vec3(x, y, z));
}

void Static_Object::addRotation(float x, float y, float z)
{
	World_Transform.rotate(glm::vec3(x, y, z));
}
