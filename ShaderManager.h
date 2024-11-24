#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <memory>
#include "Shader.h"

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();

	void loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath);
	void useShader(const std::string& name) const;
	Shader& getShader(const std::string& name) const;
private:
	GLuint getShaderProgram(const std::string& name) const;
	std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
};

#endif // !SHADERMANAGER_H