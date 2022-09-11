#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

#include "Shader.hpp"
//#include "ShaderManager.hpp"
#include "../OpenGLError.hpp"
#include "../renderer/Renderer.hpp"
//#include "../../../LevekEngine/LevekError.hpp"
#ifndef PLATFORM_WINDOWS
	#include "GlslangCompiler.hpp"
#endif

namespace Levek {

Shader::Shader(const Shader&& s): renderer_id(ShaderManager::requestShader(s.renderer_id)) {
	LEVEK_RENDERING_ID_INFO("moved shader", s.renderer_id);
}
	
Shader& Shader::operator=(Shader&& other) {
    renderer_id = ShaderManager::requestShader(other.renderer_id);//std::move(other.renderer_id);
	LEVEK_RENDERING_ID_INFO("moved assigned shader", other.renderer_id);
	return *this;
}

Shader::Shader(const Shader& s): renderer_id(ShaderManager::requestShader(s.renderer_id)) { }

Shader& Shader::operator=(Shader& other) {	
	if (this != &other) {
		renderer_id = ShaderManager::requestShader(other.renderer_id);
	}
    return *this;
}


//helper function to read source
void readShaderFromSource(std::string sourcePath, std::string& sourceCode) {

	std::ifstream file(sourcePath);
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			sourceCode += line + '\n';
		}
		file.close();
	}
	else {
		DEBUG_M("Could not open the source file of shader");
	}

}

void Shader::inizializeFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	readShaderFromSource(vertexShaderPath, vertexShaderSource);
	readShaderFromSource(fragmentShaderPath, fragmentShaderSource);
	//sudo apt install -y libgmock-dev
	//here check the correctness
#ifndef PLATFORM_WINDOWS
	GlslangCompiler compiler;

	/*
	if (!compiler.compileWithFailure(vertexShaderPath, vertexShaderSource)) {
		LEVEK_RENDERING_FAIL(compiler.getErrorMessage().c_str());
	}

	if (!compiler.compileWithFailure(fragmentShaderPath, fragmentShaderSource)) {
		LEVEK_RENDERING_FAIL(compiler.getErrorMessage().c_str());
	}*/

	compiler.compileWithFailure(fragmentShaderPath, fragmentShaderSource);
	compiler.compileWithFailure(vertexShaderPath, vertexShaderSource);
#endif
	this->renderer_id = ShaderManager::requestShader(vertexShaderSource, fragmentShaderSource);
}

void Shader::inizializeFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	this->renderer_id = ShaderManager::requestShader(vertexShaderSource, fragmentShaderSource);
}

Shader::~Shader() {
	ShaderManager::releaseShader(this->renderer_id);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const {
	GL_CHECK(glUniform4f(ShaderManager::getUniformLocation(renderer_id, name), v0, v1, v2, v3));
}

void Shader::setUniform1f(const std::string& name, float v) const {
	GL_CHECK(glUniform1f(ShaderManager::getUniformLocation(renderer_id, name), v));
}

void Shader::setUniform1f(const std::string& name, float* v, size_t size) const {
	GL_CHECK(glUniform1fv(ShaderManager::getUniformLocation(renderer_id, name), size, (const GLfloat*)&v[0]));
}

void Shader::setUniform2f(const std::string& name, const glm::vec2& v) const {
	GL_CHECK(glUniform2f(ShaderManager::getUniformLocation(renderer_id, name), v.x, v.y));
}

void Shader::setUniform3f(const std::string& name, const glm::vec3& v) const {
	GL_CHECK(glUniform3f(ShaderManager::getUniformLocation(renderer_id, name), v.x, v.y, v.z));
}

void Shader::setUniform4f(const std::string& name, const glm::vec4* v, size_t size) const {
	GL_CHECK(glUniform4fv(ShaderManager::getUniformLocation(renderer_id, name), size, (const GLfloat*)&v[0]));
}

void Shader::setUniform4f(const std::string& name, const glm::vec4& v) const {
	//bool res = glIsProgram(this->renderer_id) == GL_TRUE;
	GLint params = -1;
	glGetProgramiv(this->renderer_id, GL_LINK_STATUS, &params);
	bool res = params == GL_TRUE;
	float a = v.x;
	GL_CHECK(glUniform4f(ShaderManager::getUniformLocation(renderer_id, name), v.x, v.y, v.z, v.w));
}

void Shader::setUniform1i(const std::string& name, int v) const {
	GL_CHECK(glUniform1i(ShaderManager::getUniformLocation(renderer_id, name), v));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& m) const {
	GL_CHECK(glUniformMatrix4fv(ShaderManager::getUniformLocation(renderer_id, name), 1, GL_FALSE, &m[0][0])); //1 matrix and do we need to transpose it, we also give a pointer to the first element
}

void Shader::setUniformMat3f(const std::string& name, const glm::mat3& m) const {
	GL_CHECK(glUniformMatrix3fv(ShaderManager::getUniformLocation(renderer_id, name), 1, GL_FALSE, &m[0][0])); //1 matrix and do we need to transpose it, we also give a pointer to the first element
}

/*void Shader::setUniformMat3f(const std::string& name, const std::vector<glm::mat3>& arr) const {
	GL_CHECK(glUniformMatrix3fv(ShaderManager::getUniformLocation(renderer_id, name), arr.size(), GL_FALSE, arr[0][0] )); //1 matrix and do we need to transpose it, we also give a pointer to the first element
}*/


void Shader::bind() const {
	//LEVEK_RENDERING_ID_INFO("binding shader", renderer_id);
	GL_CHECK(glUseProgram(renderer_id));
}

void Shader::unbind() const {
	//LEVEK_RENDERING_ID_INFO("binding shader", renderer_id);
	GL_CHECK(glUseProgram(0));
}
};


