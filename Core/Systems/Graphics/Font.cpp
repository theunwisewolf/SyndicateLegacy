#include "Font.h"

namespace Syndicate { namespace Graphics {

Maths::Vector2 Font::s_Scale = Maths::Vector2(1.0f, 1.0f);

void Font::setScale(float x, float y)
{
	Font::s_Scale.x = x;
	Font::s_Scale.y = y;
}

void Font::setScale(const Maths::Vector2& scale)
{
	Font::s_Scale.x = scale.x;
	Font::s_Scale.y = scale.y;
}

Font::Font(const std::string& fontName, const float& size, const Color& color) 
	: m_FontName(fontName),
	  m_FontSize(size),
	  m_Color(color),
	  m_Atlas(nullptr)
{
	m_Font = FontManager::getFont(fontName, size);
	m_Atlas = m_Font->atlas;
}

Font::~Font() 
{
}

} }