#ifndef BUFFER_H_
#define BUFFER_H_

#include <Common.h>

namespace Syndicate { namespace Graphics {
class SYNDICATE_API Buffer;

SYNDICATE_TEMPLATE template class SYNDICATE_API std::allocator<Buffer*>;
SYNDICATE_TEMPLATE template class SYNDICATE_API std::vector<Buffer*>;

class SYNDICATE_API Buffer
{
private:
	GLuint m_BufferID;
	GLuint m_ComponentCount;

public:
	Buffer(GLfloat* data, GLsizei count, GLuint componentCount);
	Buffer(GLfloat* data, GLsizei count, GLuint componentCount, GLenum usage);

	~Buffer();

	inline void Bind()   const { glBindBuffer(GL_ARRAY_BUFFER, this->m_BufferID); };
	inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); };

	inline GLuint getComponentCount() const { return this->m_ComponentCount; };
};

}
}
#endif