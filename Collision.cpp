#include "Collision.h"
#include "gl/glew.h"
#include "Shader.h"
Collision::Collision()
{
    EBO_ = VAO_ = VBO_ = 0;
}
void Collision::setAabb(const std::vector<float>& aabb)
{
    aabb_ = aabb;
    setRenderInfo();
}

std::vector<float> Collision::getAabb() const
{
    return aabb_;
}

void Collision::drawAabb(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& model, Shader& cShader)
{
    glLineWidth(2.0f);
    cShader.useShader();
    cShader.setUniformMatrix4fv("u_Model", model);
    cShader.setUniformMatrix4fv("u_Viewing", view);
    cShader.setUniformMatrix4fv("u_Projection", proj);

    glBindVertexArray(VAO_);

    glDrawElements(GL_LINES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
    glUseProgram(0);
}

void Collision::setRenderInfo()
{
    float x = aabb_[0];
    float X = aabb_[1];
    float y = aabb_[2];
    float Y = aabb_[3];
    float z = aabb_[4];
    float Z = aabb_[5];
    std::vector<glm::vec3> points{
        {X, y, z},
        {x, y, z},
        {X, y, Z},
        {x, y, Z},
        
        {X, Y, z},
        {x, Y, z},
        {X, Y, Z},
        {x, Y, Z}
    };
    indices_ = {
        0, 1, 1, 3, 3, 2, 2, 0,
        // 상단 면
        4, 5, 5, 7, 7, 6, 6, 4,
        // 수직 연결
        0, 4, 1, 5, 2, 6, 3, 7
    };
    bindBuffers(points);
}

void Collision::bindBuffers(const std::vector<glm::vec3>& vertices)
{
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO_);
    glGenBuffers(1, &EBO_);

    glBindVertexArray(VAO_);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}
