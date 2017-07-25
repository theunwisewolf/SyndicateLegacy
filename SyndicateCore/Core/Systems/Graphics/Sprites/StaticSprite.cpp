#include "StaticSprite.h"

namespace Syndicate { namespace Graphics { 

StaticSprite::StaticSprite(glm::vec3 position, glm::vec2 size, Color color, Shader shader)
	: Renderable2D(position, size, color), m_Shader{shader}
{
	this->m_Texture = nullptr;

	GLfloat vertices[] = {
		position.x, position.y, 0,
		position.x, position.y + size.y, 0,
		position.x + size.x, position.y + size.y, 0,
		position.x + size.x, position.y, 0
	};

	GLfloat colors[] = {
		color.Red(), color.Blue(), color.Green(), color.Alpha(),
		color.Red(), color.Blue(), color.Green(), color.Alpha(),
		color.Red(), color.Blue(), color.Green(), color.Alpha(),
		color.Red(), color.Blue(), color.Green(), color.Alpha(),
	};

	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLfloat uvs[] = {
		0, 0, 
		0, 1, 
		1, 1,
		1, 0
	};

	GLfloat tid = 0.0f;

	this->m_VertexArray = synnew VertexArray();
	this->m_IndexBuffer = synnew IndexBuffer(indices, 6);

	this->m_VertexArray->addBuffer(synnew Buffer(vertices, 3 * 4, 3), 0);
	this->m_VertexArray->addBuffer(synnew Buffer(colors, 4 * 4, 4), 1);
	this->m_VertexArray->addBuffer(synnew Buffer(uvs, 2 * 4, 2), 2);
	this->m_VertexArray->addBuffer(synnew Buffer(&tid, 1, 1), 3);
}

StaticSprite::StaticSprite(glm::vec3 position, glm::vec2 size, Texture* texture, Shader shader)
	: Renderable2D(position, size, glm::vec4(1,0,0,1)), m_Shader{ shader }
{
	this->m_Texture = texture;

	GLfloat vertices[] = {
		position.x, position.y, 0,
		position.x, position.y + size.y, 0,
		position.x + size.x, position.y + size.y, 0,
		position.x + size.x, position.y, 0
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};

	GLushort indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	GLfloat uvs[] = {
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	GLfloat tid = (float)texture->GetTextureID();

	this->m_VertexArray = synnew VertexArray();
	this->m_IndexBuffer = synnew IndexBuffer(indices, 6);

	this->m_VertexArray->addBuffer(synnew Buffer(vertices, 3 * 4, 3), 0);
	this->m_VertexArray->addBuffer(synnew Buffer(colors, 4 * 4, 4), 1);
	this->m_VertexArray->addBuffer(synnew Buffer(uvs, 2 * 4, 2), 2);
	this->m_VertexArray->addBuffer(synnew Buffer(&tid, 1, 1), 3);
}

StaticSprite::~StaticSprite()
{
	delete this->m_IndexBuffer;
	delete this->m_VertexArray;
}

} }