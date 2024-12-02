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
	glm::vec3 getPosition() const { return worldTransform_.getLocation(); }
	glm::mat4 getModel() const { return worldTransform_.getTransformMatrix(); }
	void addMesh(const std::shared_ptr<Mesh>& mesh);
	void setScale(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void addScale(float x, float y, float z);
	void addPosition(float x, float y, float z);
	void addRotation(float x, float y, float z);

protected:
	std::vector<std::shared_ptr<Mesh>> meshes_;
	ModelMatrix worldTransform_;
};


class Object : public Static_Object {
public:
	Object();
	~Object();
	

	void drawGrid(const glm::mat4& view, const glm::mat4& proj);
	void addGrid();
	virtual void update(float frameTime);

	const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;
	void addMesh(const std::shared_ptr<Mesh>& mesh);

	void adjustDelta(float x, float y, float z);
	void adjustDeltaX(float delta);
	void adjustDeltaY(float delta);
	void adjustDeltaZ(float delta);

	void adjustRotate(float x, float y, float z);
	void adjustRotateX(float delta);
	void adjustRotateY(float delta);
	void adjustRotateZ(float delta);

	void setOrDeleteState(char type, bool DorS);
	void setObjectState(char type);
	void deleteObjectState(char type);
	bool isOnGround();
protected:
	
protected:
	Grid* grid_;

	Movement movement_;
	std::unordered_set<char> collisionStates_;
};