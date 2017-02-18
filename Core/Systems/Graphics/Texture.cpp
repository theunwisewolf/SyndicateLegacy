#include "Texture.h"

namespace Venus { namespace Graphics { 

Texture::Texture(const std::string& filename)
	: m_Filename(filename)
{
	FIBITMAP* dataInBits = Utilities::loadImage(filename.c_str(), &this->m_Width, &this->m_Height);
	BYTE* pixels = FreeImage_GetBits( dataInBits );

	glGenTextures(1, &this->m_TextureID);
	glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_Width, this->m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	// Unload the image since we have loaded in OpenGL
	FreeImage_Unload(dataInBits);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->m_TextureID);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	//glDeleteTextures(1, &this->m_TextureID);
}

}}