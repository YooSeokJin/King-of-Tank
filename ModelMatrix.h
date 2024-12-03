#pragma once
#include "glm/glm.hpp"

class ModelMatrix {
public:
	ModelMatrix();
	ModelMatrix(const glm::vec3& center, const glm::vec3& scale, float rZ);
	~ModelMatrix();
	// 위치 Set, Get
	glm::vec3 getLocation() const;
	float getLocationX() const;
	float getLocationY() const;
	float getLocationZ() const;

	void setLocation(const glm::vec3& newLocation);
	void setLocationX(float newX);
	void setLocationY(float newY);
	void setLocationZ(float newZ);

	void moveLocation(const glm::vec3& deltaPosition);
	void moveLocationX(float deltaX);
	void moveLocationY(float deltaY);
	void moveLocationZ(float deltaZ);


	// 회전 Set, Get
	glm::vec3 getRotation() const;
	float getRotationX() const;
	float getRotationY() const;
	float getRotationZ() const;

	void setRotation(const glm::vec3& newAngle);
	void setRotationX(float newAngleX);
	void setRotationY(float newAngleY);
	void setRotationZ(float newAngleZ);

	void rotate(const glm::vec3& deltaAngle);
	void rotateX(float deltaAngle);
	void rotateY(float deltaAngle);
	void rotateZ(float deltaAngle);

	float getYaw() const;
	// 스케일 Set, Get
	glm::vec3 getScale() const;
	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;

	void setScale(const glm::vec3& newScale);
	void setScaleX(float newX);
	void setScaleY(float newY);
	void setScaleZ(float newZ);

	void scale(const glm::vec3& deltaScale);
	void scaleX(float deltaX);
	void scaleY(float deltaY);
	void scaleZ(float deltaZ);

	void resetAll();
	void resetLocationRotation();
	void setPivot(float x, float y, float z);
	void setPivot(const glm::vec3& pivot);

	glm::mat4 getTransformMatrix() const;

	void setParent(ModelMatrix* p);
	void deleteParent();

	glm::vec3 getForwardVector() const;

	glm::vec3* pivotPoint_;
private:
	ModelMatrix* parent_ = nullptr;
	glm::vec3 location_;
	glm::vec3 rotation_;
	glm::vec3 scale_;
};
