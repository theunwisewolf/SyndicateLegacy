#include "Buffer.h"

#include <iostream>
namespace Venus { namespace Graphics {
Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount) :
	m_ComponentCount(componentCount)
{
	glGenBuffers(1, &this->m_BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_BufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * count, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &this->m_BufferID);
}

}}