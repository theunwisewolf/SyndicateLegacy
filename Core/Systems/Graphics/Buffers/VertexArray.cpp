#include "VertexArray.h"
#include <iostream>
namespace Venus { namespace Graphics {

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &this->m_ArrayID);
}

VertexArray::~VertexArray()
{
	for (auto buffer : this->m_Buffers)
	{
		delete buffer;
	}

	glDeleteVertexArrays(1, &this->m_ArrayID);
}

void VertexArray::addBuffer(Buffer* buffer, GLuint index)
{
	this->Bind();
	buffer->Bind();
	
	glEnableVertexAttribArray(index);

	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	buffer->Unbind();
	this->Unbind();

	this->m_Buffers.push_back(buffer);
}

}}