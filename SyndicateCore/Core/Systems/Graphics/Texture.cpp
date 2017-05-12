#include "Texture.h"

namespace Syndicate { namespace Graphics { 

Texture::Texture() :
	m_Width(0),
	m_Height(0),
	m_TextureData(nullptr)
{
	m_Parameters = TextureParameters{ TextureFormat::RGBA, TextureWrap::CLAMP_TO_EDGE, TextureFilter::NEAREST };
	Texture::LoadTexture();
}

Texture::Texture(unsigned int width, unsigned int height) :
	m_Width(width),
	m_Height(height),
	m_TextureData(nullptr)
{
	m_Parameters = TextureParameters{ TextureFormat::RGBA, TextureWrap::CLAMP_TO_EDGE, TextureFilter::NEAREST };
	Texture::LoadTexture();
}

Texture::Texture(ImageData* image) :
	m_TextureData(image)
{
	m_Parameters = TextureParameters{ TextureFormat::RGBA, TextureWrap::CLAMP_TO_EDGE, TextureFilter::NEAREST };
	Texture::LoadTexture();
}


Texture::Texture(unsigned int width, unsigned int height, TextureParameters params) :
	m_Width(width),
	m_Height(height),
	m_Parameters(params),
	m_TextureData(nullptr)
{
	Texture::LoadTexture();
}

Texture::Texture(ImageData* image, TextureParameters params) : 
	m_Parameters(params),
	m_TextureData(image)
{
	Texture::LoadTexture();
}

void Texture::SetData(const void* data)
{
	GL(glBindTexture(GL_TEXTURE_2D, this->m_TextureID));
	//GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, this->m_Width, this->m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, data));
	GL(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, this->m_Width, this->m_Height, (GLint)m_Parameters.format, GL_UNSIGNED_BYTE, data));
}

void Texture::LoadTexture()
{	
	BYTE* pixels = nullptr;

	// We have a texture
	if (this->m_TextureData != nullptr)
	{
		// Make sure the texture file exists, otherwise send a warning
		/*if (!Utilities::File::Exists(this->m_Filename))
		{
			SYNDICATE_WARNING("Texture file " + this->m_Filename + " does not exist.");
			return;
		}*/

		this->m_Width = m_TextureData->width;
		this->m_Height = m_TextureData->height;

		pixels = Utilities::loadImageFromMemory((unsigned char*)&m_TextureData->data[0], m_TextureData->length, &this->m_Width, &this->m_Height);
	}

	// Generate 1 texture
	GL(glGenTextures(1, &this->m_TextureID));

	// Bind it
	GL(glBindTexture(GL_TEXTURE_2D, this->m_TextureID));

	// Setup our texture parameters
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)m_Parameters.filter));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)m_Parameters.filter));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)m_Parameters.wrap));
	GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)m_Parameters.wrap));
	
	// Upload to GPU
	GL(glTexImage2D(GL_TEXTURE_2D, 0, (GLint)m_Parameters.format, this->m_Width, this->m_Height, 0, (GLint)m_Parameters.format, GL_UNSIGNED_BYTE, pixels));
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_Width, this->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	// Generate MipMaps
	//GL(glGenerateMipmap(GL_TEXTURE_2D));

	// Unbind the texture
	GL(glBindTexture(GL_TEXTURE_2D, 0));

	// Unload the image since we have loaded in OpenGL
	if (pixels != nullptr)
	{
		free(pixels);
	}
}

void Texture::Bind() const
{
	GL(glBindTexture(GL_TEXTURE_2D, this->m_TextureID));
}

void Texture::Unbind() const
{
	GL(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture::~Texture()
{
	GL(glDeleteTextures(1, &this->m_TextureID));
}

}}