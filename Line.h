#pragma once
#include <string>
#include <vector>
#include "Shader.h"
#include "glm/glm.hpp"
class Line{
public:
	Line();
	~Line();
	virtual void update() = 0;

	void setUp();
	void draw(const glm::mat4& view, const glm::mat4& proj);

	void setStartPoint(const glm::vec3& point);
	void setEndPoint(const glm::vec3& point);
	void setColor(const glm::vec3& color);

protected:
	unsigned int VBO_;
	unsigned int VAO_;

	glm::vec3 startPosition_;
	glm::vec3 endPosition_;

	glm::vec3 lineColor_;

	Shader* lineShader_;
	bool isDirty_;
	char tag_ = 'N';
};

