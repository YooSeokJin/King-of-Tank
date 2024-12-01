#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader {
public:
	Shader() : programID_(0) { }
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();


	void useShader() const;
	GLuint getProgramID() const { return programID_; }

	void setUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const;
	void setUniformVec4(const std::string& name, const glm::vec4& vec) const;
	void setUniformVec3(const std::string& name, const glm::vec3& vec) const;
	void setUniformVec2(const std::string& name, const glm::vec2& vec) const;
	void setUniformFloat(const std::string& name, float value) const;
	void setUniformInt(const std::string& name, int value) const;

private:
	GLint getUniformLocation(const std::string& name) const;
	bool readFile(const char* filename, std::string* target);
	void addShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint compileShader(const char* fileNameVS, const char* fileNameFS);

protected:
	GLuint programID_;
	mutable std::unordered_map<std::string, GLint> uniformCache_;
};
