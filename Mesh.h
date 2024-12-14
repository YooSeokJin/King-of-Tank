#pragma once
#include <string>
#include <vector>
#include "Collision.h"
#include "ModelMatrix.h"
#include "glm/glm.hpp"

class Movement;

class Mesh {
public:
	Mesh();
	~Mesh();
	virtual void update(float frameTime);

	void chanegIndex();
	void addMovement();
	void drawAabb(const glm::mat4& view, const glm::mat4& proj, Shader& cShader);
	void applyMovement();
	void addPosition(const glm::vec3& position);
	void addNormal(const glm::vec3& normal);
	void addTexCoord(const glm::vec2& texcoord);

	void addIndex(unsigned int index);
	void addNormalIndex(unsigned int index);
	void addTexCoordIndex(unsigned int index);
	
	
	std::vector<float> assembleVertexData();

	std::string& getShaderName() { return shaderName_; }
	void setShaderName(const std::string& name) { shaderName_ = name; }

	void setParent(ModelMatrix* parent);
	void deleteParent();
	void setPivot(float x, float y, float z);
	void setPivot(const glm::vec3& pivot);

	const std::vector<glm::vec3>& getPositions() const { return positions_; }
	const std::vector<glm::vec3>& getNormals()const { return normals_; }
	const std::vector<glm::vec2>& getTexCoords() const { return texCoords_; }
	const std::vector<unsigned int>& getIndices() const { return assembleIndices_; }

	glm::mat4 getModelTransform() const { return localTransform_.getTransformMatrix(); }
	unsigned int& getVAO() { return VAO_; }
	unsigned int& getVBO() { return VBO_; }
	unsigned int& getEBO() { return EBO_; }

	glm::vec4* meshColor_;
	int textureType_ = -1;

	Movement* movement_ = nullptr;
	ModelMatrix localTransform_;

	void showAllVertices();
	void showPositions() const;

	void addCollision();
	std::vector<float> getAabb() const;

	void init();
private:
	Collision aabb_;
	std::vector<glm::vec3> positions_;
	std::vector<glm::vec3> normals_;
	std::vector<glm::vec2> texCoords_;

	std::vector<unsigned int> indices_;
	std::vector<unsigned int> normalIndices_;
	std::vector<unsigned int> texcoordsIndices_;

	std::vector<unsigned int> assembleIndices_;

	std::string shaderName_;
	unsigned int VAO_, VBO_, EBO_;
};
