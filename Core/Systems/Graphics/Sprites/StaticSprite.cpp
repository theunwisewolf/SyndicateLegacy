#include "StaticSprite.h"

namespace Venus { namespace Graphics { 

StaticSprite::StaticSprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color, Shader shader)
	: Renderable2D(position, size, color), m_Shader{shader}
{
	GLfloat vertices[] = {
		position.x, position.y, 0,
		position.x, position.y + size.y, 0,
		position.x + size.x, position.y + size.y, 0,
		position.x + size.x, position.y, 0
	};

	/*GLfloat vertices[] = {
	0,0,0,
	0,size.y,0,
	size.x,size.y,0,
	size.x,0,0,
	};*/

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

	this->m_VertexArray = new VertexArray();
	this->m_IndexBuffer = new IndexBuffer(indices, 6);

	this->m_VertexArray->addBuffer(new Buffer(vertices, 3 * 4, 3), 0);
	this->m_VertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);
}

StaticSprite::~StaticSprite()
{
	delete this->m_IndexBuffer;
	delete this->m_VertexArray;
}

} }