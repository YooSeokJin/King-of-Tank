#include <iostream>
#include <fstream>
#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	programID = CompileShader(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	if (programID != 0)
		glDeleteProgram(programID);
}

void Shader::useShader() const
{
	glUseProgram(programID);
}

void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4& mat) const
{
	GLuint location = getUniformLocation(name);
	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
}

void Shader::setUniformVec4(const std::string& name, const glm::vec4& vec) const
{
	GLuint location = getUniformLocation(name);
	if (location != -1)
		glUniform4fv(location, 1, &vec[0]);
}

void Shader::setUniformVec3(const std::string& name, const glm::vec3& vec) const
{
	GLuint location = getUniformLocation(name);
	if (location != -1)
		glUniform3fv(location, 1, &vec[0]);
}

void Shader::setUniformVec2(const std::string& name, const glm::vec2& vec) const
{
	GLuint location = getUniformLocation(name);
	glUniform2fv(location, 1, &vec[0]);
}

void Shader::setUniformFloat(const std::string& name, float value) const
{
	GLuint location = getUniformLocation(name);
	if (location != -1)
		glUniform1f(location, value);
}

void Shader::setUniformInt(const std::string& name, int value) const
{
	GLuint location = getUniformLocation(name);
	if (location != -1)
		glUniform1i(location, value);
}


void Shader::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	// 쉐이더 오브젝트 생성
	GLuint shaderObj = glCreateShader(ShaderType);

	if (shaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1]{ };
	p[0] = pShaderText;
	GLint Lengths[1]{ };
	Lengths[0] = static_cast<GLint>(strlen(pShaderText));
	// 쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(shaderObj, 1, p, Lengths);

	// 할당된 쉐이더 코드를 컴파일
	glCompileShader(shaderObj);

	// shaderObj가 성공적으로 컴파일 되었는지 확인
	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		// OpenGL의 shader log 데이터를 가져옴
		glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error Compiling shader type %d: '%s;\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// Shader Program에 Attach
	glAttachShader(ShaderProgram, shaderObj);
	glDeleteShader(shaderObj);
}
GLint Shader::getUniformLocation(const std::string& name) const
{
	if (uniformCache.find(name) != uniformCache.end()) {
		return uniformCache[name];
	}
	GLint location = glGetUniformLocation(programID, name.c_str());
	if (location == -1) {
		std::cerr << "Warning: uniform '" << name << "' doesn't exist in shader program.\n";
	}

	// 위치를 캐시에 저장
	uniformCache[name] = location;

	return location;
}
bool Shader::ReadFile(const char* filename, std::string* target)
{
	std::ifstream file(filename);
	if (!file) {
		std::cerr << filename << " file loading failed... \n";
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}
GLuint Shader::CompileShader(const char* fileNameVS, const char* fileNameFS)
{
	// 빈 쉐이더 프로그램 생성.
	GLuint shaderProgram = glCreateProgram();

	if (shaderProgram == 0) {
		fprintf(stderr, "Error creating shader program\n");
	}
	// vs가 로딩되었는지 체크
	std::string vs, fs;
	if (!ReadFile(fileNameVS, &vs)) {
		std::cerr << "Error compiling vertex shader\n";
	}
	// fs가 로딩되었는지 체크
	if (!ReadFile(fileNameFS, &fs)) {
		std::cerr << "Error compiling fragment shader\n";
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint success = 0;
	GLchar ErrorLog[1024] = { 0 };

	// Attach 완료된 shaderProgram을 링킹
	glLinkProgram(shaderProgram);

	// 링크가 성공했는지 확인
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (success == 0) {
		// shader program 로그를 받아온다.
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cerr << fileNameVS << ", " << fileNameFS << " Error linking shader program" << ErrorLog;
		return -1;
	}

	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << fileNameVS << ", " << fileNameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	std::cout << fileNameVS << ", " << fileNameFS << " Shader compiling is done.\n";

	return shaderProgram;
}