#include "Mesh.h"
#include "global.h"
#include "gl/glew.h"
#include "Movement.h"
#include "algorithm"

Mesh::Mesh() : VAO_(0), VBO_(0), EBO_(0)
{
    shaderName_ = { };
    meshColor_ = nullptr;
}

Mesh::~Mesh()
{
    printf("Del Mesh\n");
    delete movement_;
    delete meshColor_;
}

void Mesh::chanegIndex()
{
    if (!indices_.empty()) {
        auto min = std::min_element(indices_.begin(), indices_.end());
        unsigned int MinValue = *min;
        if (*min != 0) {
            for (auto& i : indices_) {
                i -= MinValue;
            }
        }
    }
    if (!normalIndices_.empty()) {
        auto min = std::min_element(normalIndices_.begin(), normalIndices_.end());
        unsigned int MinValue = *min;
        if (*min != 0) {
            for (auto& i : normalIndices_) {
                i -= MinValue;
            }
        }
    }
    if (!texcoordsIndices_.empty()) {
        auto min = std::min_element(texcoordsIndices_.begin(), texcoordsIndices_.end());
        unsigned int MinValue = *min;
        if (*min != 0) {
            for (auto& i : texcoordsIndices_) {
                i -= MinValue;
            }
        }
    }
}

void Mesh::addMovement()
{
    if (!movement_) movement_ = new Movement();
}

void Mesh::drawAabb(const glm::mat4& view, const glm::mat4& proj, Shader& cShader)
{
    aabb_.drawAabb(view, proj, localTransform_.getTransformMatrix(), cShader);
}

void Mesh::applyMovement()
{
    glm::mat4 tr = localTransform_.getTransformMatrix();
    for (auto& v : positions_) {
        glm::vec4 newPos = glm::vec4(v, 1);
        v = tr * newPos;
    }
    localTransform_.resetAll();
}

void Mesh::addPosition(const glm::vec3& position)
{
    positions_.emplace_back(position);
}

void Mesh::addNormal(const glm::vec3& normal)
{
    normals_.emplace_back(normal);
}

void Mesh::addTexCoord(const glm::vec2& texcoord)
{
    texCoords_.emplace_back(texcoord);
}

void Mesh::addIndex(unsigned int index)
{
    indices_.push_back(index);
}

void Mesh::addNormalIndex(unsigned int index)
{
    normalIndices_.push_back(index);
}

void Mesh::addTexCoordIndex(unsigned int index)
{
    texcoordsIndices_.push_back(index);
}

void Mesh::update(float frameTime)
{
    if (!movement_) return;
    movement_->update(frameTime);

    localTransform_.moveLocation(movement_->getDeltaPosition());
    localTransform_.rotate(movement_->getDeltaRotation());
}


std::vector<float> Mesh::assembleVertexData()
{
    chanegIndex();
    std::vector<float> vertexData;
    for (size_t i = 0; i < indices_.size(); ++i) {
        // Position
        size_t idx_index = indices_[i];
        vertexData.push_back(positions_[idx_index].x);
        vertexData.push_back(positions_[idx_index].y);
        vertexData.push_back(positions_[idx_index].z);
        // Normal
        if (normals_.empty()) {
            vertexData.push_back(0.f);
            vertexData.push_back(0.f);
            vertexData.push_back(0.f);
        }
        else {
            size_t normal_idx = normalIndices_[i];
            vertexData.push_back(normals_[normal_idx].x);
            vertexData.push_back(normals_[normal_idx].y);
            vertexData.push_back(normals_[normal_idx].z);
        }
        // TexCoords
        if (texCoords_.empty()) {
            vertexData.push_back(0.f);
            vertexData.push_back(0.f);
        }
        else {
            size_t texcoords_idx = texcoordsIndices_[i];
            vertexData.push_back(texCoords_[texcoords_idx].x);
            vertexData.push_back(texCoords_[texcoords_idx].y);
        }
        // Color
        if (meshColor_) {
            vertexData.push_back(meshColor_->r);
            vertexData.push_back(meshColor_->g);
            vertexData.push_back(meshColor_->b);
            vertexData.push_back(meshColor_->a);
        }
        else {
            vertexData.push_back(0.1f);
            vertexData.push_back(0.1f);
            vertexData.push_back(0.1f);
            vertexData.push_back(1.0f);
        }
        assembleIndices_.push_back(static_cast<unsigned int>(i));
    }
    return vertexData;
}

void Mesh::setParent(ModelMatrix* parent)
{
    localTransform_.setParent(parent);
}

void Mesh::deleteParent()
{
    localTransform_.deleteParent();
}

void Mesh::setPivot(float x, float y, float z)
{
    localTransform_.setPivot(x, y, z);
}

void Mesh::setPivot(const glm::vec3& pivot)
{
    localTransform_.setPivot(pivot);
}

void Mesh::showAllVertices() {
    glm::mat4 model = localTransform_.getTransformMatrix();

    std::vector<glm::vec3> newPos;

    for (const auto& v : positions_) {
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

void Mesh::showPositions() const
{
    auto a = localTransform_.getLocation();
    printf("%f, %f, %f\n", a.x, a.y, a.z);
}

void Mesh::addCollision()
{
    glm::mat4 model = localTransform_.getTransformMatrix();

    std::vector<glm::vec3> newPos;

    for (const auto& v : positions_) {
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
    aabb_.setAabb(pos);
}

std::vector<float> Mesh::getAabb() const
{
    std::vector<float> aabb_world = aabb_.getAabb();

    glm::vec4 minPoint(aabb_world[0], aabb_world[2], aabb_world[4], 1.0f);
    glm::vec4 maxPoint(aabb_world[1], aabb_world[3], aabb_world[5], 1.0f);

    glm::mat4 model = localTransform_.getTransformMatrix();

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

void Mesh::init()
{
    /*positions.clear();
    normals.clear();
    texCoords.clear();
    indices.clear();
    normals.clear();
    texCoords.clear();*/
}
