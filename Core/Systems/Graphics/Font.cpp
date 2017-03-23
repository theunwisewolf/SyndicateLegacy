#include "Font.h"

namespace Venus { namespace Graphics {

Font::Font(const std::string& fontName, const float& size, const unsigned int& color) 
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