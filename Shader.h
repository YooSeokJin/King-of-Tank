#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader {
public:
	Shader() : programID(0) { }
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();


	void useShader() const;
	GLuint getProgramID() const { return programID; }

	void setUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const;
	void setUniformVec4(const std::string& name, const glm::vec4& vec) const;
	void setUniformVec3(const std::string& name, const glm::vec3& vec) const;
	void setUniformVec2(const std::string& name, const glm::vec2& vec) const;
	void setUniformFloat(const std::string& name, float value) const;
	void setUniformInt(const std::string& name, int value) const;

private:
	GLint getUniformLocation(const std::string& name) const;
	bool ReadFile(const char* filename, std::string* target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShader(const char* fileNameVS, const char* fileNameFS);

protected:
	GLuint programID;
	mutable std::unordered_map<std::string, GLint> uniformCache;
};

#endif // !SHADER_H