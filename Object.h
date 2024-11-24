#pragma once
#include <vector>
#include <memory>
#include "Mesh.h"
#include "Movement.h"

class Grid;
class Static_Object {
public:
	Static_Object();
	virtual void update(float frameTime);
	const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;
	glm::vec3 getPosition() const { return World_Transform.getLocation(); }
	void addMesh(const std::shared_ptr<Mesh>& mesh);
	void setScale(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void addScale(float x, float y, float z);
	void addPosition(float x, float y, float z);
	void addRotation(float x, float y, float z);
protected:
	std::vector<std::shared_ptr<Mesh>> meshes;
	ModelMatrix World_Transform;
};


class Object : public Static_Object {
public:
	Object();
	~Object();

	void DrawGrid(const glm::mat4& view, const glm::mat4& proj);
	void addGrid();
	virtual void update(float frame_time);

	const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;
	void addMesh(const std::shared_ptr<Mesh>& mesh);

	void adjustDelta(float x, float y, float z);
	void adjustRotate(float x, float y, float z);
protected:
	
protected:
	Grid* grid;

	Movement move;
};