#include "Font.h"

namespace Venus { namespace Graphics {

Font::Font(const std::string& fontName, const float& size, const unsigned int& color, bool create) 
	: m_FontName(fontName),
	  m_FontSize(size),
	  m_Color(color),
	  m_Atlas(nullptr)
{
	if (create)
	{
		this->createFontAtlas();
		m_Font = FontManager::getFont(fontName, m_Atlas, size);
	}
}

// Assuming Atlas has been created
void Font::Init()
{
	if (m_Atlas != nullptr)
	{
		m_Font = FontManager::getFont(m_FontName, m_Atlas, m_FontSize);
	}
}

void Font::createFontAtlas(int width, int height, int depth)
{
	m_Atlas = texture_atlas_new(width, height, depth);
}

Font::~Font() 
{

}

} }