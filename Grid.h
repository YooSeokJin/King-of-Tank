#ifndef GRID_H
#define GRID_H

#include <vector>
#include "glm/mat4x4.hpp"
#include "Shader.h"
class Camera;
class Shader;

class Grid {
public:
	Grid();
	~Grid();
	
	void draw(const glm::mat4& viewing, const glm::mat4& proj, const glm::mat4& model);
private:
	std::vector<float> grids;
	std::vector<unsigned int> indices;
	Shader* gridShader;
	unsigned int gridVBO;
	unsigned int gridVAO;
	unsigned int gridEBO;
};
#endif