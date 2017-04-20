#ifndef FONT_H_
#define FONT_H_

#include <string>
#include <Utilities/Maths/Maths.h>
#include <Systems/Graphics/Texture.h>
#include <Systems/Graphics/FontManager.h>
#include <Systems/Graphics/Color.h>
#include <freetype-gl.h>

#include <Common.h>

namespace Syndicate { namespace Graphics { 

class SYNDICATE_API Font {
private:
	static Maths::Vector2 s_Scale;

public:
	static const Maths::Vector2& getScale() { return Font::s_Scale; };
	static void setScale(const Maths::Vector2& scale);
	static void setScale(float x, float y);

private:  
    std::string m_FontName;
    float m_FontSize;
	Color m_Color;
	Texture* m_Texture;

	texture_font_t* m_Font;
	texture_atlas_t* m_Atlas;
	 
public: 
	Font(const std::string& fontName, const float& size, const Color& color);
	~Font();

	void setColor(Maths::Vector4 color) { m_Color = color; }
	void setSize(float size) { m_FontSize = size; }
	void setFont(std::string fontName) { m_FontName = fontName; }

	inline const std::string& getFontName() const { return m_FontName; }
	inline const float& getSize() const { return m_FontSize; }
	inline const Color& getColor() const { return m_Color; }
	inline Texture* getTexture() const { return m_Texture; }
	inline texture_atlas_t* getAtlas() const { return m_Atlas; }
	inline texture_font_t* getFont() const { return m_Font; }
};

} }

#endif