#include "ShaderManager.h"
#include <iostream>

ShaderManager::ShaderManager()
{
	// 셰이더 로드
	loadShader("Model", "./shaders/model.VS", "./shaders/model.FS");
	loadShader("LightSource", "./shaders/lightSource.VS", "./shaders/lightSource.FS");
	loadShader("Collision", "./shaders/collision.VS", "./shaders/collision.FS");
}
ShaderManager::~ShaderManager()
{
	shaders_.clear();
}
void ShaderManager::loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath)
{
	if (shaders_.find(name) != shaders_.end()) {
		return;
	}
	shaders_[name] = std::make_shared<Shader>(vertexPath, fragmentPath);
}

void ShaderManager::useShader(const std::string& name) const
{
	auto it = shaders_.find(name);
	if (it == shaders_.end()) {
		std::cerr << "Shader \'" << name << "\' not found.Please load the shader first." << std::endl;
		throw std::runtime_error("Shader not found");
	}
	it->second->useShader();
}

Shader& ShaderManager::getShader(const std::string& name) const
{
	auto it = shaders_.find(name);
	if (it == shaders_.end()) {
		std::cerr << "Shader \'" << name << "\' not found.Please load the shader first." << std::endl;
		throw std::runtime_error("Shader not found");
	}
	//it->second->useShader();
	return *it->second;
}

GLuint ShaderManager::getShaderProgram(const std::string& name) const
{
	auto it = shaders_.find(name);
	if (it == shaders_.end()) {
		std::cerr << "Shader " << name << " not found" << std::endl;
		return -1;
	}
	return it->second->getProgramID();
}