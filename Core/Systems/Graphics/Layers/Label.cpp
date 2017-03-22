#include "Label.h"

namespace Venus { namespace Graphics { 

Label::Label(std::string text, Maths::Vector2 position) :
	m_Text(text),
	m_Position(position)
{
	// Create an atlas
	m_FontAtlas = texture_atlas_new(512, 512, 1);
	m_Font = texture_font_new_from_file(m_FontAtlas, 100, "res/Fonts/Roboto-Regular.ttf");

	// Generate the OpenGL Texture
	glGenTextures(1, &m_FontAtlas->id);

	// Set the texture parameters
	glBindTexture(GL_TEXTURE_2D, m_FontAtlas->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Label::Submit(Renderer2D* renderer) const 
{
	renderer->DrawString(m_Text, m_Position, m_FontAtlas, m_Font);
}

Label::~Label()
{
	texture_font_delete(m_Font);
	texture_atlas_delete(m_FontAtlas);
}

} }