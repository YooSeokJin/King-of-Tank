#include "Grid.h"
#include "gl/glew.h"
#include "glm/gtc/matrix_transform.hpp"
Grid::Grid()
	: gridVAO_(0), gridVBO_(0)
{
	float gsize = 2.5f;
	gridShader_ = new Shader("./shaders/grid.VS", "./shaders/grid.FS");

	gridVertices_ = {
		// xyz rgba
		-gsize, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
		 gsize, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
		
		0.f, -gsize, 0.f, 0.f, 1.f, 0.f, 1.f,
		0.f,  gsize, 0.f, 0.f, 1.f, 0.f, 1.f,
		
		0.f, 0.f, -gsize, 0.f, 0.f, 1.f, 1.f,
		0.f, 0.f,  gsize, 0.f, 0.f, 1.f, 1.f,
	
	};

	gridIndices_ = {
		1, 0, 
		2, 3, 
		4, 5  
	};

	const size_t stride = 7 * sizeof(float);

	glGenVertexArrays(1, &gridVAO_);
	glGenBuffers(1, &gridVBO_);
	glGenBuffers(1, &gridEBO_);

	glBindVertexArray(gridVAO_);

	glBindBuffer(GL_ARRAY_BUFFER, gridVBO_);
	glBufferData(GL_ARRAY_BUFFER, gridVertices_.size() * sizeof(float), gridVertices_.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gridEBO_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, gridIndices_.size() * sizeof(unsigned int), gridIndices_.data(), GL_STATIC_DRAW);

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
	if (gridVBO_ != 0) glDeleteBuffers(1, &gridVBO_);
	if (gridVAO_ != 0) glDeleteVertexArrays(1, &gridVAO_);
}

void Grid::draw(const glm::mat4& viewing, const glm::mat4& proj, const glm::mat4& model)
{
	glUseProgram(0);
	glLineWidth(2.0f);
	gridShader_->useShader();
	gridShader_->setUniformMatrix4fv("u_Model", model);
	gridShader_->setUniformMatrix4fv("u_Viewing", viewing);
	gridShader_->setUniformMatrix4fv("u_Projection", proj);

	glBindVertexArray(gridVAO_);

	glDrawElements(GL_LINES, static_cast<GLsizei>(gridIndices_.size()), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}
