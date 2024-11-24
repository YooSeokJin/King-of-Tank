#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager()
{
	// 셰이더 로드
	loadShader("Model", "./shaders/model.VS", "./shaders/model.FS");
}
ShaderManager::~ShaderManager()
{
	shaders.clear();
}
void ShaderManager::loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath)
{
	if (shaders.find(name) != shaders.end()) {
		return;
	}
	shaders[name] = std::make_shared<Shader>(vertexPath, fragmentPath);
}

void ShaderManager::useShader(const std::string& name) const
{
	auto it = shaders.find(name);
	if (it == shaders.end()) {
		std::cerr << "Shader \'" << name << "\' not found.Please load the shader first." << std::endl;
		throw std::runtime_error("Shader not found");
	}
	it->second->useShader();
}

Shader& ShaderManager::getShader(const std::string& name) const
{
	auto it = shaders.find(name);
	if (it == shaders.end()) {
		std::cerr << "Shader \'" << name << "\' not found.Please load the shader first." << std::endl;
		throw std::runtime_error("Shader not found");
	}
	//it->second->useShader();
	return *it->second;
}

GLuint ShaderManager::getShaderProgram(const std::string& name) const
{
	auto it = shaders.find(name);
	if (it == shaders.end()) {
		std::cerr << "Shader " << name << " not found" << std::endl;
		return -1;
	}
	return it->second->getProgramID();
}