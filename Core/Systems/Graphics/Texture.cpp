#include "Texture.h"
#include <iostream>
namespace Syndicate { namespace Graphics { 

Texture::Texture(const std::string& filename)
	: m_Filename(filename)
{
}

void Texture::loadTexture()
{
	// Make sure the texture file exists, otherwise send a warning
	if (!Utilities::File::Exists(this->m_Filename))
	{
		SYNDICATE_WARNING("Texture file " + this->m_Filename + " does not exist.");
		return;
	}

	FIBITMAP* dataInBits = Utilities::loadImage(this->m_Filename.c_str(), &this->m_Width, &this->m_Height);
	BYTE* pixels = FreeImage_GetBits(dataInBits);
	
	// Generate 1 texture
	glGenTextures(1, &this->m_TextureID);

	// Bind it
	glBindTexture(GL_TEXTURE_2D, this->m_TextureID);

	// Setup our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Upload to GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_Width, this->m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	// Unbind the texture
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
	glDeleteTextures(1, &this->m_TextureID);
}

}}