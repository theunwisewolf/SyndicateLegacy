#include "StaticSprite.h"

namespace Venus { namespace Graphics { 

StaticSprite::StaticSprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color, Shader shader)
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
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
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

	this->m_VertexArray = new VertexArray();
	this->m_IndexBuffer = new IndexBuffer(indices, 6);

	this->m_VertexArray->addBuffer(new Buffer(vertices, 3 * 4, 3), 0);
	this->m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
	this->m_VertexArray->addBuffer(new Buffer(uvs, 2 * 4, 2), 2);
	this->m_VertexArray->addBuffer(new Buffer(&tid, 1, 1), 3);
}

StaticSprite::StaticSprite(Maths::Vector3 position, Maths::Vector2 size, Texture* texture, Shader shader)
	: Renderable2D(position, size, Maths::Vector4(1,0,0,1)), m_Shader{ shader }
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

	GLfloat tid = (float)texture->getTextureID();

	this->m_VertexArray = new VertexArray();
	this->m_IndexBuffer = new IndexBuffer(indices, 6);

	this->m_VertexArray->addBuffer(new Buffer(vertices, 3 * 4, 3), 0);
	this->m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
	this->m_VertexArray->addBuffer(new Buffer(uvs, 2 * 4, 2), 2);
	this->m_VertexArray->addBuffer(new Buffer(&tid, 1, 1), 3);
}

StaticSprite::~StaticSprite()
{
	delete this->m_IndexBuffer;
	delete this->m_VertexArray;
}

} }