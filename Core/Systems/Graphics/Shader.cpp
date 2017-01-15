#include "Shader.h"

namespace Venus { namespace Graphics {
Shader::Shader()
{
}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) :
	m_vertexShaderPath{vertexShaderPath},
	m_fragmentShaderPath{fragmentShaderPath}
{
	this->m_ShaderID = this->load();
}

Shader::~Shader()
{
	glDeleteProgram(this->m_ShaderID);
}

GLuint Shader::load()
{
	GLuint shaderProgram = glCreateProgram();
	GLuint vertexShader  = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::string vertShaderData;
	std::string fragShaderData;

	// For logging
	GLint success;
	GLint length;

	try
	{
		vertShaderData = Utilities::File(this->m_vertexShaderPath).Read().getData();
		fragShaderData = Utilities::File(this->m_fragmentShaderPath).Read().getData();
	}
	catch (Utilities::VException& e)
	{
		std::cout << e.what();
		return -1;
	}

	const char* vData = vertShaderData.c_str();
	const char* fData = fragShaderData.c_str();

	glShaderSource(vertexShader, 1, &vData, NULL);
	glShaderSource(fragmentShader, 1, &fData, NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(vertexShader, length, &length, &error[0]);

		std::cout << "Failed to compile Vertex Shader: " << std::endl << &error[0] << std::endl;

		glDeleteShader(vertexShader);
		return -1;
	}

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragmentShader, length, &length, &error[0]);

		std::cout << "Failed to compile Fragment Shader: " << std::endl << &error[0] << std::endl;

		glDeleteShader(fragmentShader);
		return -1;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetProgramInfoLog(shaderProgram, length, &length, &error[0]);

		std::cout << "Failed to link shader program: " << std::endl << &error[0] << std::endl;

		glDeleteProgram(shaderProgram);
		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void Shader::enable() const 
{
	glUseProgram(this->m_ShaderID);
}

void Shader::disable() const
{
	glUseProgram(0);
}

GLint Shader::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(this->m_ShaderID, name);
}

GLint Shader::getAttributeLocation(const GLchar* name)
{
	return glGetAttribLocation(this->m_ShaderID, name);
}

void Shader::setUniform1i(const GLchar* name, int value)
{
	glUniform1i(this->getUniformLocation(name), value);
}

void Shader::setUniform1f(const GLchar* name, float value)
{
	glUniform1f(this->getUniformLocation(name), value);
}

void Shader::setUniform2f(const GLchar* name, const Maths::Vector2& vector)
{
	glUniform2f(this->getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniform3f(const GLchar* name, const Maths::Vector3& vector)
{
	glUniform3f(this->getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const GLchar* name, const Maths::Vector4& vector)
{
	glUniform4f(this->getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMat4(const GLchar* name, const Maths::Matrix4& matrix)
{
	glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, matrix.elements);
}

}}