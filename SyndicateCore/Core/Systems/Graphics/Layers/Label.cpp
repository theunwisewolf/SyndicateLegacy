#include "Label.h"

namespace Syndicate { namespace Graphics { 

Label::Label(std::string text, glm::vec2 position, Font font) :
	m_TextHeight(0.0f),
	m_TextWidth(0.0f),
	m_Text(text),
	m_Position(position),
	m_Font(font)
{
	e_PositionParameter = Position::LEFT;
	Init();
}

Label::Label(std::string text, Position position, Font font) :
	m_TextHeight(0.0f),
	m_TextWidth(0.0f),
	m_Text(text),
	m_Font(font)
{
	e_PositionParameter = position;

	Init();
	ReAlign();
}

void Label::ReAlign()
{
	switch (e_PositionParameter)
	{
		case Position::CENTER:
			m_Position = glm::vec2(-(m_TextWidth / 2.0f), -(m_TextHeight / 2.0f));
		break;
		case Position::LEFT:
			m_Position = glm::vec2(0.0f, 0.0f);
		break;
		case Position::RIGHT:
			m_Position = glm::vec2(m_TextWidth, 0.0f);
		break;
	}
}

void Label::Init()
{
	// Create an atlas
	//m_Atlas = *texture_atlas_new(512, 512, 1);
	//m_FTFont = *texture_font_new_from_file(&m_Atlas, 50, "res/Fonts/Raleway/Raleway-Bold.ttf");

	// Because Maps are too slow for data retrieval, so we dereference the data and cache it
	m_Atlas = *m_Font.getAtlas();
	m_FTFont = *m_Font.getFont();

	for (int i = 0; i < m_Text.length(); ++i)
	{
		texture_glyph_t* glyph = texture_font_get_glyph(&m_FTFont, &m_Text[i]);

		using namespace std;
		m_TextHeight = max((float)glyph->height, m_TextHeight);
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
	renderer->DrawString(m_Text, m_Position, m_Font);
}

Label::~Label()
{
	delete m_Font.getTexture();
}

} }