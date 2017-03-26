#include "Label.h"

namespace Venus { namespace Graphics { 

Label::Label(std::string text, Maths::Vector2 position, Font font) :
	m_TextHeight(0.0f),
	m_TextWidth(0.0f),
	m_Text(text),
	m_Position(position),
	m_Font(font),
	e_PositionParameter(Position::LEFT)
{
	Init();
}

Label::Label(std::string text, Position position, Font font) :
	m_TextHeight(0.0f),
	m_TextWidth(0.0f),
	m_Text(text),
	m_Font(font),
	e_PositionParameter(position)
{
	Init();
	ReAlignText();
}

void Label::ReAlignText()
{
	switch (e_PositionParameter)
	{
		case Position::CENTER:
			m_Position = Maths::Vector2(-(m_TextWidth / 2.0f), m_TextHeight / 2.0f);
		break;
		case Position::LEFT:
			m_Position = Maths::Vector2(0.0f, 0.0f);
		break;
		case Position::RIGHT:
			m_Position = Maths::Vector2(m_TextWidth, 0.0f);
		break;
	}

}

void Label::Init()
{
	// Create an atlas
	//m_Atlas = *texture_atlas_new(512, 512, 1);
	//m_FTFont = *texture_font_new_from_file(&m_Atlas, 50, "res/Fonts/Raleway/Raleway-Bold.ttf");

	// Because Maps are too slow for data retrieval, so we derefernce the data and cache it
	m_Atlas = *m_Font.getAtlas();
	m_FTFont = *m_Font.getFont();

	// Generate the OpenGL Texture
	glGenTextures(1, &m_Atlas.id);

	// Set the texture parameters
	glBindTexture(GL_TEXTURE_2D, m_Atlas.id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	for (int i = 0; i < m_Text.length(); ++i)
	{
		texture_glyph_t* glyph = texture_font_get_glyph(&m_FTFont, &m_Text[i]);

		m_TextHeight = std::max((float)glyph->height, m_TextHeight);
		m_TextWidth += glyph->width;
	}

	m_TextWidth /= m_Font.getScale().x;
	m_TextHeight /= m_Font.getScale().y;
}

void Label::Debug()
{
	std::cout << "Text \"" << m_Text << "\": (" << m_TextWidth << ", " << m_TextHeight << ")" << std::endl;
}

void Label::Submit(Renderer2D* renderer) const 
{
	renderer->DrawString(m_Text, m_Position, m_Font.getColor(), (texture_atlas_t *)&m_Atlas, (texture_font_t *)&m_FTFont);
}

Label::~Label()
{
	/*if (m_Font)
	{
		texture_font_delete(m_Font);
		m_Font = nullptr;
	}

	if (m_FontAtlas)
	{
		texture_atlas_delete(m_FontAtlas);
		m_FontAtlas = nullptr;
	}*/

}

} }