#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

#include <GL/glew.h>
#include <Utilities/Image.h>

namespace Venus { namespace Graphics { 

class Texture {
private:
	GLuint m_TextureID;
	GLsizei m_Width;
	GLsizei m_Height;

	std::string m_Filename;
	
public:
	Texture(const std::string& filename);
	~Texture();

	void bind() const;
	void unbind() const;
	void loadTexture();

	inline const GLsizei getWidth() const { return this->m_Width; }
	inline const GLsizei getHeight() const { return this->m_Height; }
	inline const GLsizei getTextureID() const { return this->m_TextureID; }
};

} }

#endif