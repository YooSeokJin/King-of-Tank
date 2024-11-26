#pragma once
#include <unordered_set>
#include <vector>
#include <memory>
#include "Mesh.h"
#include "Movement.h"

class Grid;
class Static_Object {
public:
	Static_Object();
	virtual void update(float frameTime);
	void Init();
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
	virtual void update(float frameTime);

	const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;
	void addMesh(const std::shared_ptr<Mesh>& mesh);

	void adjustDelta(float x, float y, float z);
	void adjustDelta_X(float delta);
	void adjustDelta_Y(float delta);
	void adjustDelta_Z(float delta);

	void adjustRotate(float x, float y, float z);
	void adjustRotate_X(float delta);
	void adjustRotate_Y(float delta);
	void adjustRotate_Z(float delta);

	void set_Collision_State(char type);
	void reset_Collision_State(char type);
protected:
	
protected:
	Grid* grid;

	Movement move;
	std::unordered_set<char> collision_state;
};