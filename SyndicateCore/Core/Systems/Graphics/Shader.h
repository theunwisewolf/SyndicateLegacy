#ifndef SHADER_H_
#define SHADER_H_

#include <Common.h>

#include <vector>
#include <string>
#include <iostream>

#include <Utilities\Maths\Maths.h>
#include <Utilities/File.h>
#include <Utilities/VException.h>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API Shader
{
private:
	unsigned int m_ShaderID = -1;
	bool m_ShaderEnabled = false;
	bool m_Freed;

	std::string m_vertexShaderPath;
	std::string m_fragmentShaderPath;

public:
	Shader();
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
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
	void setUniform2f(const char* name, const Maths::Vector2& vector);
	void setUniform3f(const char* name, const Maths::Vector3& vector);
	void setUniform4f(const char* name, const Maths::Vector4& vector);
	void setUniformMat4(const char* name, const Maths::Matrix4& matrix);

	int getShaderID() const { return this->m_ShaderID; }

private:
	unsigned int load();

};

}}

#endif