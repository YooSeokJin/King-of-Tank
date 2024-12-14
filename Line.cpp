#include "Line.h"
#include "gl/glew.h"
Line::Line()
	: startPosition_(0), endPosition_(10.f, 10.f, 10.f), VBO_(0), VAO_(0), lineColor_(0.f, 1.f, 0.f)
{
	isDirty_ = false;
    lineShader_ = new Shader("./shaders/Line.VS", "./shaders/Line.FS");
}
Line::~Line()
{
    delete lineShader_;
    if (VBO_ != 0) glDeleteBuffers(1, &VBO_);
    if (VAO_ != 0) glDeleteVertexArrays(1, &VAO_);
}
void Line::setUp()
{
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);

    float vertices[6] = {
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void Line::draw(const glm::mat4& view, const glm::mat4& proj)
{
    glUseProgram(0);

    lineShader_->useShader();

    lineShader_->setUniformMatrix4fv("u_View", view);
    lineShader_->setUniformMatrix4fv("u_Projection", proj);

    lineShader_->setUniformVec3("u_Color", lineColor_);

    glBindVertexArray(VAO_);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);

    glUseProgram(0);
}
void Line::setStartPoint(const glm::vec3& point)
{
	startPosition_ = point;
}

void Line::setEndPoint(const glm::vec3& point)
{
	endPosition_ = point;
}


void Line::setColor(const glm::vec3& color)
{
	lineColor_ = color;
}
