#include "Mesh.h"
#include "global.h"
#include "gl/glew.h"
#include "Movement.h"
#include "algorithm"

Mesh::Mesh() : VAO(0), VBO(0), EBO(0)
{
	shaderName = { };
    Color = nullptr;
}

Mesh::~Mesh()
{
    delete move;
    delete Color;
}

void Mesh::change_Index()
{
    if (!indices.empty()) {
        auto min = std::min_element(indices.begin(), indices.end());
        unsigned int MinValue = *min;
        if (*min != 0) {
            for (auto& i : indices) {
                i -= MinValue;
            }
        }
    }
}

void Mesh::add_movement()
{
    if (!move) move = new Movement();
}

void Mesh::apply_movement()
{
    glm::mat4 tr = Local_Transform.getTransformMatrix();
    for (auto& v : positions) {
        glm::vec4 newPos = glm::vec4(v, 1);
        v = tr * newPos;
    }
    Local_Transform.resetAll();
}

void Mesh::add_position(const glm::vec3& position)
{
	positions.emplace_back(position);
}

void Mesh::add_normal(const glm::vec3& normal)
{
	normals.emplace_back(normal);
}

void Mesh::add_texCoord(const glm::vec2& texcoord)
{
	texCoords.emplace_back(texcoord);
}

void Mesh::add_indices(unsigned int index)
{
	indices.push_back(index);
}

void Mesh::update(float frameTime)
{
    if (!move) return;
    move->update(frameTime);

    Local_Transform.translate(move->get_delta_position());
    Local_Transform.rotate(move->get_delta_rotation());
}


std::vector<float> Mesh::assembleVertexData() const
{
    std::vector<float> vertexData;
    int colorIndex = 0;
    for (size_t i = 0; i < positions.size(); ++i) {
        // Position
        vertexData.push_back(positions[i].x);
        vertexData.push_back(positions[i].y);
        vertexData.push_back(positions[i].z);

        // Color
        if (!Color) {
            glm::vec4 Color_ = colorPalette[colorIndex % 40];
            vertexData.push_back(Color_.r);
            vertexData.push_back(Color_.g);
            vertexData.push_back(Color_.b);
            vertexData.push_back(Color_.a);
            ++colorIndex;
        }
        else {
            vertexData.push_back(Color->r);
            vertexData.push_back(Color->g);
            vertexData.push_back(Color->b);
            vertexData.push_back(Color->a);
        }

        //// Normal
        //if (i < normals.size()) {
        //    vertexData.push_back(normals[i].x);
        //    vertexData.push_back(normals[i].y);
        //    vertexData.push_back(normals[i].z);
        //}
        //else {
        //    vertexData.push_back(0.0f);
        //    vertexData.push_back(0.0f);
        //    vertexData.push_back(0.0f);
        //}

        //// TexCoord
        //if (i < texCoords.size()) {
        //    vertexData.push_back(texCoords[i].x);
        //    vertexData.push_back(texCoords[i].y);
        //}
        //else {
        //    vertexData.push_back(0.0f);
        //    vertexData.push_back(0.0f);
        //}
    }
    return vertexData;
}

void Mesh::set_Parent(ModelMatrix* p)
{
    Local_Transform.setParent(p);
}

void Mesh::delete_Parent()
{
    Local_Transform.deleteParent();
}

void Mesh::set_Pivot(float x, float y, float z)
{
    Local_Transform.setPivot(x, y, z);
}

void Mesh::set_Pivot(const glm::vec3& pivot)
{
    Local_Transform.setPivot(pivot);
}

void Mesh::show_all_vertex() {
    glm::mat4 model = Local_Transform.getTransformMatrix();

    std::vector<glm::vec3> newPos;

    for (const auto& v : positions) {
        glm::vec4 transformed = model * glm::vec4(v, 1.0f);
        newPos.emplace_back(transformed.x, transformed.y, transformed.z);
    }

    auto minmaxX = std::minmax_element(newPos.begin(), newPos.end(), 
        [](const glm::vec3& v1, const glm::vec3& v2) {
        return v1.x < v2.x;
        });

    auto minmaxY = std::minmax_element(newPos.begin(), newPos.end(), 
        [](const glm::vec3& v1, const glm::vec3& v2) {
        return v1.y < v2.y;
        });

    auto minmaxZ = std::minmax_element(newPos.begin(), newPos.end(), 
        [](const glm::vec3& v1, const glm::vec3& v2) {
        return v1.z < v2.z;
        });

    printf("minX: %f, maxX: %f\n", minmaxX.first->x, minmaxX.second->x);
    printf("minY: %f, maxY: %f\n", minmaxY.first->y, minmaxY.second->y);
    printf("minZ: %f, maxZ: %f\n", minmaxZ.first->z, minmaxZ.second->z);

    printf("\n\n");
}

void Mesh::show_position() const
{
    auto a = Local_Transform.getLocation();
    printf("%f, %f, %f\n", a.x, a.y, a.z);
}

void Mesh::add_collision()
{
    glm::mat4 model = Local_Transform.getTransformMatrix();

    std::vector<glm::vec3> newPos;

    for (const auto& v : positions) {
        glm::vec4 transformed = model * glm::vec4(v, 1.0f);
        newPos.emplace_back(transformed.x, transformed.y, transformed.z);
    }

    auto minmaxX = std::minmax_element(newPos.begin(), newPos.end(),
        [](const glm::vec3& v1, const glm::vec3& v2) {
            return v1.x < v2.x;
        });

    auto minmaxY = std::minmax_element(newPos.begin(), newPos.end(),
        [](const glm::vec3& v1, const glm::vec3& v2) {
            return v1.y < v2.y;
        });

    auto minmaxZ = std::minmax_element(newPos.begin(), newPos.end(),
        [](const glm::vec3& v1, const glm::vec3& v2) {
            return v1.z < v2.z;
        });
    std::vector<float> pos;
    pos.push_back(minmaxX.first->x);
    pos.push_back(minmaxX.second->x);
    pos.push_back(minmaxY.first->y);
    pos.push_back(minmaxY.second->y);
    pos.push_back(minmaxZ.first->z);
    pos.push_back(minmaxZ.second->z);
    aabb.set_aabb(pos);
}

std::vector<float> Mesh::get_aabb()
{
    std::vector<float> aabb_world = aabb.get_aabb();

    glm::vec4 minPoint(aabb_world[0], aabb_world[2], aabb_world[4], 1.0f);
    glm::vec4 maxPoint(aabb_world[1], aabb_world[3], aabb_world[5], 1.0f);

    glm::mat4 model = Local_Transform.getTransformMatrix();

    glm::vec4 transformedMin = model * minPoint;
    glm::vec4 transformedMax = model * maxPoint;

    glm::vec3 newMin(
        std::min(transformedMin.x, transformedMax.x),
        std::min(transformedMin.y, transformedMax.y),
        std::min(transformedMin.z, transformedMax.z)
    );
    glm::vec3 newMax(
        std::max(transformedMin.x, transformedMax.x),
        std::max(transformedMin.y, transformedMax.y),
        std::max(transformedMin.z, transformedMax.z)
    );

    return {
        newMin.x, newMax.x,
        newMin.y, newMax.y,
        newMin.z, newMax.z
    };
}