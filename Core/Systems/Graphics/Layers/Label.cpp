#include "Label.h"

namespace Venus { namespace Graphics { 

Label::Label(std::string text, Maths::Vector2 position) :
	m_Text(text),
	m_Position(position)
{
	// Create an atlas
	m_FontAtlas = texture_atlas_new(512, 512, 3);
	m_Font = texture_font_new_from_file(m_FontAtlas, 80, "res/Fonts/Roboto-Regular.ttf");

	// Generate the OpenGL Texture
	glGenTextures(1, &m_FontAtlas->id);
}

void Label::Submit(Renderer2D* renderer) const 
{
	//renderer->drawString(m_Text, m_Position, m_FontAtlas, m_Font);
	//renderer->drawString(m_Text, m_Position, nullptr, nullptr);
}

Label::~Label()
{
	//texture_font_delete(m_Font);
	//texture_atlas_delete(m_FontAtlas);
}

} }