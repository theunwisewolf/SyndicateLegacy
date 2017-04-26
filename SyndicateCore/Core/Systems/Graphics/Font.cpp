#include "Font.h"

namespace Syndicate { namespace Graphics {

void Font::setScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void Font::setScale(const Maths::Vector2& scale)
{
	m_Scale.x = scale.x;
	m_Scale.y = scale.y;
}

Font::Font(const std::string& fontName, const float& size, const Color& color, const Maths::Vector2& scale) :
	m_FontName(fontName),
	m_FontSize(size),
	m_Color(color),
	m_Atlas(nullptr),
	m_Scale(1.0f, 1.0f)
{
	m_Scale = scale;
	m_Font = FontManager::getFont(fontName, size);

	if (!m_Font)
	{
		SYNDICATE_ERROR("Unable to load font " + fontName);
		return;
	}

	m_Atlas = m_Font->atlas;

	TextureParameters parameters{
		TextureFormat::RED,
		TextureWrap::CLAMP_TO_EDGE,
		TextureFilter::LINEAR
	};

	m_Texture = synnew Texture(m_Atlas->width, m_Atlas->height, parameters);
	m_Font->atlas->id = m_Atlas->id = m_Texture->GetTextureID();
	
	m_Texture->SetData(m_Atlas->data);
}

Font::~Font() 
{
}

} }