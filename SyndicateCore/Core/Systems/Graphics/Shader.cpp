#include "Shader.h"

namespace Syndicate { namespace Graphics {
Shader::Shader() :
	m_Freed(false),
	m_ShaderEnabled(false),
	m_ShaderID(-1)
{
	// Use default fallback shaders
	m_vertexShaderPath = "Shaders/VertexShader.vert";
	m_fragmentShaderPath = "Shaders/FragmentShader.frag";

	this->m_ShaderEnabled = false;
	this->m_ShaderID = this->load();

	int textureSlots[] = { 0,1,2,3,4,5,6,7,8,9 };
	this->Enable();
	this->setUniform1iv("textures", textureSlots, 10);
}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) :
	m_vertexShaderPath{vertexShaderPath},
	m_fragmentShaderPath{fragmentShaderPath},
	m_Freed(false),
	m_ShaderEnabled(false),
	m_ShaderID(-1)
{
	this->m_ShaderEnabled = false;
	this->m_ShaderID = this->load();
}

void Shader::Free()
{
	if (!m_Freed)
	{
		GL(glDeleteProgram(this->m_ShaderID));
		m_Freed = true;
	}
}

Shader::~Shader()
{
	this->Free();
}

unsigned int Shader::load()
{
	unsigned int shaderProgram  = glCreateProgram();
	unsigned int vertexShader   = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	std::string vertShaderData;
	std::string fragShaderData;

	// For logging
	int success;
	int length;

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

	GL(glShaderSource(vertexShader, 1, &vData, NULL));
	GL(glShaderSource(fragmentShader, 1, &fData, NULL));

	GL(glCompileShader(vertexShader));
	GL(glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		GL(glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length));
		std::vector<char> error(length);
		GL(glGetShaderInfoLog(vertexShader, length, &length, &error[0]));

		std::cout << "Failed to compile Vertex Shader: " << std::endl << &error[0] << std::endl;

		GL(glDeleteShader(vertexShader));
		return -1;
	}

	GL(glCompileShader(fragmentShader));
	GL(glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success));

	if (!success)
	{
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
		std::vector<char> error(length);
		glGetShaderInfoLog(fragmentShader, length, &length, &error[0]);

		std::cout << "Failed to compile Fragment Shader: " << std::endl << &error[0] << std::endl;

		glDeleteShader(fragmentShader);
		return -1;
	}

	GL(glAttachShader(shaderProgram, vertexShader));
	GL(glAttachShader(shaderProgram, fragmentShader));

	GL(glLinkProgram(shaderProgram));
	GL(glValidateProgram(shaderProgram));
	GL(glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success));

	if (!success)
	{
		GL(glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length));
		std::vector<char> error(length);
		GL(glGetProgramInfoLog(shaderProgram, length, &length, &error[0]));

		std::cout << "Failed to link shader program: " << std::endl << &error[0] << std::endl;

		GL(glDeleteProgram(shaderProgram));
		return -1;
	}

	GL(glDeleteShader(vertexShader));
	GL(glDeleteShader(fragmentShader));

	return shaderProgram;
}

void Shader::Enable() 
{
	this->m_ShaderEnabled = true;
	GL(glUseProgram(this->m_ShaderID));
}

void Shader::Disable()
{
	this->m_ShaderEnabled = false;
	GL(glUseProgram(0));
}

int Shader::getUniformLocation(const char* name)
{
	if (this->m_ShaderEnabled == false)
	{
		this->Enable();
		SYNDICATE_ERROR("Shader was not enabled while setting value: " + std::string(name));
	}

	return glGetUniformLocation(this->m_ShaderID, name);
}

int Shader::getAttributeLocation(const char* name)
{
	return glGetAttribLocation(this->m_ShaderID, name);
}

void Shader::setUniform1i(const char* name, int value)
{
	GL(glUniform1i(this->getUniformLocation(name), value));
}

void Shader::setUniform1f(const char* name, float value)
{
	GL(glUniform1f(this->getUniformLocation(name), value));
}

void Shader::setUniform2f(const char* name, const Maths::Vector2& vector)
{
	GL(glUniform2f(this->getUniformLocation(name), vector.x, vector.y));
}

void Shader::setUniform3f(const char* name, const Maths::Vector3& vector)
{
	GL(glUniform3f(this->getUniformLocation(name), vector.x, vector.y, vector.z));
}

void Shader::setUniform4f(const char* name, const Maths::Vector4& vector)
{
	GL(glUniform4f(this->getUniformLocation(name), vector.x, vector.y, vector.z, vector.w));
}

void Shader::setUniformMat4(const char* name, const Maths::Matrix4& matrix)
{
	GL(glUniformMatrix4fv(this->getUniformLocation(name), 1, GL_FALSE, matrix.elements));
}

void Shader::setUniform1fv(const char* name, float* value, int count)
{
	GL(glUniform1fv(this->getUniformLocation(name), count, value));
}

void Shader::setUniform1iv(const char* name, int* value, int count)
{
	GL(glUniform1iv(this->getUniformLocation(name), count, value));
}

}}