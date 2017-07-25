#ifndef SHADER_H_
#define SHADER_H_

#include <Common.h>

#include <vector>
#include <string>
#include <iostream>

#include <Systems/ResourceManager.h>
#include <Utilities/Maths/Maths.h>

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
#include <GLM/mat4x4.hpp>

#include <Utilities/File.h>
#include <Utilities/VException.h>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API Shader
{
private:
	unsigned int m_ShaderID = -1;
	bool m_ShaderEnabled = false;
	bool m_Freed;

	std::string m_vertexShaderIdentifier;
	std::string m_fragmentShaderIdentifier;

public:
	Shader();
	Shader(std::string vertexShader, std::string fragmentShader);
	~Shader();

	void Free();

	void Enable();
	void Disable();

	int getUniformLocation(const char* name);
	int getAttributeLocation(const char* name);

	void setUniform1i(const char* name, int value);
	void setUniform1iv(const char* name, int* value, int count);
	void setUniform1f(const char* name, float value);
	void setUniform1fv(const char* name, float* value, int count);
	void setUniform2f(const char* name, const glm::vec2& vector);
	void setUniform3f(const char* name, const glm::vec3& vector);
	void setUniform4f(const char* name, const glm::vec4& vector);
	void setUniformMat4(const char* name, const glm::mat4& matrix);

	int getShaderID() const { return this->m_ShaderID; }

private:
	unsigned int load();

};

}}

#endif