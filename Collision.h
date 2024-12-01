#pragma once
#include <vector>
#include <glm/glm.hpp>

class Shader;
class Collision {
public:
	Collision();
	void setAabb(const std::vector<float>& aabb);
	std::vector<float> getAabb() const;
	void drawAabb(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& model, Shader& cShader);
protected:
	void setRenderInfo();
	void bindBuffers(const std::vector<glm::vec3>& vertices);
protected:
	std::vector<float> aabb_;
	std::vector<unsigned int> indices_;
	unsigned int VAO_, VBO_, EBO_;
};