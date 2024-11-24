#include "Grid.h"
#include "gl/glew.h"
#include "glm/gtc/matrix_transform.hpp"
Grid::Grid()
	: gridVAO(0), gridVBO(0)
{
	float gsize = 2.5f;
	gridShader = new Shader("./shaders/grid.VS", "./shaders/grid.FS");

	grids = {
		// xyz rgba
		-gsize, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
		 gsize, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
		
		0.f, -gsize, 0.f, 0.f, 1.f, 0.f, 1.f,
		0.f,  gsize, 0.f, 0.f, 1.f, 0.f, 1.f,
		
		0.f, 0.f, -gsize, 0.f, 0.f, 1.f, 1.f,
		0.f, 0.f,  gsize, 0.f, 0.f, 1.f, 1.f,
	
	};

	indices = {
		1, 0, 
		2, 3, 
		4, 5  
	};

	const size_t stride = 7 * sizeof(float);

	glGenVertexArrays(1, &gridVAO);
	glGenBuffers(1, &gridVBO);
	glGenBuffers(1, &gridEBO);

	glBindVertexArray(gridVAO);

	glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
	glBufferData(GL_ARRAY_BUFFER, grids.size() * sizeof(float), grids.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Grid::~Grid()
{
	printf("Grid Delete\n");
	if (gridVBO != 0) glDeleteBuffers(1, &gridVBO);
	if (gridVAO != 0) glDeleteVertexArrays(1, &gridVAO);
}

void Grid::draw(const glm::mat4& viewing, const glm::mat4& proj, const glm::mat4& model)
{
	glLineWidth(2.0f);
	glm::vec3 translation = glm::vec3(model[3][0], model[3][1], model[3][2]);
	glm::mat4 newModel = glm::translate(glm::mat4(1.0f), translation);
	gridShader->useShader();
	gridShader->setUniformMatrix4fv("u_Model", newModel);
	gridShader->setUniformMatrix4fv("u_Viewing", viewing);
	gridShader->setUniformMatrix4fv("u_Projection", proj);

	glBindVertexArray(gridVAO);

	glDrawElements(GL_LINES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}
