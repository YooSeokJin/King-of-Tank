#ifndef MESH_H
#define MESH_H
#include <string>
#include <vector>
#include "ModelMatrix.h"
#include "glm/glm.hpp"

class Movement;

class Mesh {
public:
	Mesh();
	~Mesh();

	void add_movement();

	void apply_movement();
	void add_position(const glm::vec3& position);
	void add_normal(const glm::vec3& normal);
	void add_texCoord(const glm::vec2& texcoord);
	
	void add_indices(unsigned int index);
	virtual void update(float frameTime);
	std::vector<float> assembleVertexData() const;

	std::string& get_ShaderName() { return shaderName; }
	void set_ShaderName(const std::string& name) { shaderName = name; }

	void set_Parent(ModelMatrix* p);
	void delete_Parent();
	void set_Pivot(float x, float y, float z);
	void set_Pivot(const glm::vec3& pivot);

	const std::vector<glm::vec3>& get_positions() const { return positions; }
	const std::vector<glm::vec3>& get_normals()const { return normals; }
	const std::vector<glm::vec2>& get_texCoords() const { return texCoords; }
	const std::vector<unsigned int>& get_indices() const { return indices; }
	glm::mat4 get_modelTransform() { return Local_Transform.getTransformMatrix(); }
	unsigned int& getVAO() { return VAO; }
	unsigned int& getVBO() { return VBO; }
	unsigned int& getEBO() { return EBO; }

	glm::vec4* Color;

	Movement* move = nullptr;
	ModelMatrix Local_Transform;

	void show_all_vertex();
	void show_position() const;

	std::vector<glm::vec2> get_aabb();
private:
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<unsigned int> indices;
	std::string shaderName;
	unsigned int VAO, VBO, EBO;
};
#endif

