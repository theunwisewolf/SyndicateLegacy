#include "IndexBuffer.h"

namespace Venus { namespace Graphics {

IndexBuffer::IndexBuffer(GLushort* data, GLsizei count) :
	m_Count(count)
{
	glGenBuffers(1, &this->m_BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * count, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &this->m_BufferID);
}

} }