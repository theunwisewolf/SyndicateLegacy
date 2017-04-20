#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <Common.h>
#include <Utilities/Logger.h>
#include <Utilities/File.h>

#include <string>

#include <Utilities/Image.h>

namespace Syndicate { namespace Graphics { 

enum class TextureFormat {
	RED = GL_RED,
	RGB = GL_RGB,
	BGR = GL_BGR,
	RGBA = GL_RGBA,
};

enum class TextureWrap {
	REPEAT = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,

	CLAMP  = GL_CLAMP,
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
};

enum class TextureFilter {
	LINEAR = GL_LINEAR,
	NEAREST = GL_NEAREST,
};

struct TextureParameters {
	TextureFormat format;
	TextureWrap wrap;
	TextureFilter filter;
};

class SYNDICATE_API Texture {
private:
	unsigned int m_TextureID;
	unsigned int m_Width;
	unsigned int m_Height;

	std::string m_Filename;
	TextureParameters m_Parameters;
	
public:
	Texture();
	Texture(const std::string& filename);
	Texture(unsigned int width, unsigned int height);

	Texture(unsigned int width, unsigned int height, TextureParameters params);
	Texture(const std::string& filename, TextureParameters params);
	~Texture();

	void Bind() const;
	void Unbind() const;
	void LoadTexture();
	
	void SetParameters(TextureParameters params) { this->m_Parameters = params; };
	void SetData(const void* data);
	void SetWidth(unsigned int width) { this->m_Width = width; }
	void SetHeight(unsigned int height) { this->m_Height = height; }
	void SetTextureID(unsigned int id) { this->m_TextureID = id; }

	inline const int GetWidth() const { return this->m_Width; }
	inline const int GetHeight() const { return this->m_Height; }
	inline const int GetTextureID() const { return this->m_TextureID; }
};

} }

#endif