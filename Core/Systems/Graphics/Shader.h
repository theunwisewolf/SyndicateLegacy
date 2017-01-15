#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <string>
#include <iostream>

#include <GL/glew.h>
#include <Utilities\Maths\Maths.h>
#include <Utilities/File.h>
#include <Utilities/VException.h>

namespace Venus { namespace Graphics {

class Shader
{
private:
	GLuint m_ShaderID = -1;

	std::string m_vertexShaderPath;
	std::string m_fragmentShaderPath;

public:
	Shader();
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);
	~Shader();

	void enable() const;
	void disable() const;

	GLint getUniformLocation(const GLchar* name);
	GLint getAttributeLocation(const GLchar* name);

	void setUniform1i(const GLchar* name, int value);
	void setUniform1f(const GLchar* name, float value);
	void setUniform2f(const GLchar* name, const Maths::Vector2& vector);
	void setUniform3f(const GLchar* name, const Maths::Vector3& vector);
	void setUniform4f(const GLchar* name, const Maths::Vector4& vector);
	void setUniformMat4(const GLchar* name, const Maths::Matrix4& matrix);

	GLuint getShaderID() const { return this->m_ShaderID; }

private:
	GLuint load();

};

}}

#endif