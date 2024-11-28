#ifndef MESH_H
#define MESH_H
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
	void change_Index();
	void add_movement();

	void apply_movement();
	void add_position(const glm::vec3& position);
	void add_normal(const glm::vec3& normal);
	void add_texCoord(const glm::vec2& texcoord);

	void add_indices(unsigned int index);
	void add_normal_indices(unsigned int index);
	void add_texcoords_indices(unsigned int index);

	virtual void update(float frameTime);
	std::vector<float> assembleVertexData();

	std::string& get_ShaderName() { return shaderName; }
	void set_ShaderName(const std::string& name) { shaderName = name; }

	void set_Parent(ModelMatrix* p);
	void delete_Parent();
	void set_Pivot(float x, float y, float z);
	void set_Pivot(const glm::vec3& pivot);

	const std::vector<glm::vec3>& get_positions() const { return positions; }
	const std::vector<glm::vec3>& get_normals()const { return normals; }
	const std::vector<glm::vec2>& get_texCoords() const { return texCoords; }
	const std::vector<unsigned int>& get_indices() const { return assemble_indices; }

	glm::mat4 get_modelTransform() const { return Local_Transform.getTransformMatrix(); }
	unsigned int& getVAO() { return VAO; }
	unsigned int& getVBO() { return VBO; }
	unsigned int& getEBO() { return EBO; }

	glm::vec4* Color;

	Movement* move = nullptr;
	ModelMatrix Local_Transform;

	void show_all_vertex();
	void show_position() const;

	void add_collision();
	std::vector<float> get_aabb() const;

	void Init();
private:
	Collision aabb;
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;

	std::vector<unsigned int> indices;
	std::vector<unsigned int> normal_indices;
	std::vector<unsigned int> texcoords_indices;

	std::vector<unsigned int> assemble_indices;

	std::string shaderName;
	unsigned int VAO, VBO, EBO;
};
#endif

