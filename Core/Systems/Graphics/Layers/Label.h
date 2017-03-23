#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <Utilities/Maths/Maths.h>
#include <freetype-gl.h>
#include <Systems/Graphics/Font.h>
#include <Systems/Graphics/FontManager.h>

namespace Venus { namespace Graphics { 

class Label : public Renderable2D
{
private:
	std::string m_Text;
	Maths::Vector2 m_Position;

	// Fonts
	texture_atlas_t* m_FontAtlas;
	texture_font_t* m_Font;

public:
    Label(std::string text, Maths::Vector2 position, Font font);
	~Label();
	void Submit(Renderer2D* renderer) const override;
	void setText(const std::string& text) { this->m_Text = text; }
};

}}

#endif