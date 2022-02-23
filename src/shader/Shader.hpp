#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>

#include "glm/glm.hpp"
#include "ShaderManager.hpp"

namespace Levek {

/**
 * This class represents a shader. It is made out of some vertex shader and some
 * fragment shader. It contains functions that allows setting uniforms in the shader
 * program.
 */
class Shader {

private:
	unsigned int renderer_id;

protected:
	Shader(): renderer_id(0) {}

	/**
	 * 
	 */
	void inizializeFromFile(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	
	/**
	 * 
	 */
	void inizializeFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
public:

	//since this class is a shell class for the managed opengl shaders we need
	//to make sure that when we move the object or when we copy it that we
	//take special care to the shader id reference. Namely, we need to request another
	//managed shader. This is because when we move the object the object from will be destroyed and
	//will decrease its reference count. When copying we also need to increase the reference
	//count. Refere to the ShaderManager class for implementation details
	Shader(const Shader&& s); //move constructor
	Shader& operator=(Shader&& other); //move assigned operator

	Shader(const Shader& s); // copy constructor
	Shader& operator=(Shader& other); //copy assignment operator

	/**
	 * Destructor of the Shader class
	 */
	~Shader();

	/**
	 * Binds the shader object
	 */
	void bind() const;

	/**
	 * Unbinds the shader object
	 */
	void unbind() const;


	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
	void setUniform4f(const std::string& name, const glm::vec4& v) const;
	void setUniform4f(const std::string& name, const glm::vec4* v, size_t size) const;

	void setUniform3f(const std::string& name, const glm::vec3& v) const;
	void setUniform2f(const std::string& name, const glm::vec2& v) const;

	void setUniform1i(const std::string& name, int v) const;
	void setUniform1f(const std::string& name, float v) const;
	void setUniformMat3f(const std::string& name, const glm::mat3& m) const;
	void setUniformMat4f(const std::string& name, const glm::mat4& m) const;
	friend class ShaderFactory;

private:
	std::unordered_map<std::string, int> uniformLocationCache;
	int getUniformLocation(const std::string& name);
};
}