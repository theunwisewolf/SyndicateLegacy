#ifndef INDEX_BUFFER_H_
#define INDEX_BUFFER_H_

#include <GL/glew.h>

namespace Venus { namespace Graphics {

class IndexBuffer
{
private:
	GLuint m_BufferID;
	GLsizei m_Count;

public:
	IndexBuffer(GLushort* data, GLsizei count);
	IndexBuffer(GLuint* data, GLsizei count);
	~IndexBuffer();

	inline void Bind()   const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_BufferID); };
	inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); };

	inline GLuint getCount() const { return this->m_Count; };
};

} }

#endif 