#pragma once
#include <vector>
#include "glm/mat4x4.hpp"
#include "Shader.h"

class Grid {
public:
	Grid();
	~Grid();
	
	void draw(const glm::mat4& viewing, const glm::mat4& proj, const glm::mat4& model);
private:
	std::vector<float> gridVertices_;
	std::vector<unsigned int> gridIndices_;
	Shader* gridShader_;
	unsigned int gridVBO_;
	unsigned int gridVAO_;
	unsigned int gridEBO_;
};
