#ifndef LABEL_H_
#define LABEL_H_

#include <Common.h>

#include <string>
#include <algorithm>
#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Systems/Graphics/Sprites/Renderable2D.h>

#include <freetype-gl.h>
#include <Systems/Graphics/Font.h>
#include <Systems/Graphics/FontManager.h>

#include <GLM/vec2.hpp>

namespace Syndicate { namespace Graphics { 

class SYNDICATE_API Label : public Renderable2D
{
private:
	std::string m_Text;
	glm::vec2 m_Position;

	Font m_Font;

	texture_atlas_t m_Atlas;
	texture_font_t m_FTFont;

	float m_TextWidth;
	float m_TextHeight;

public:
    Label(std::string text, glm::vec2 position, Font font);
	Label(std::string text, Position position, Font font);
	~Label();

	void Init();
	void Debug();
	void ReAlign() override;
	void Submit(Renderer2D* renderer) const override;
	void setText(const std::string& text) { this->m_Text = text; }
};

}}

#endif