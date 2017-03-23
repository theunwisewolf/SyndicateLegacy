#ifndef FONT_H_
#define FONT_H_

#include <string>
#include <Utilities/Maths/Maths.h>
#include <Systems/Graphics/FontManager.h>
#include <freetype-gl.h>

namespace Venus { namespace Graphics { 

class Font {

private:  
    std::string m_FontName;
    float m_FontSize;
	unsigned int m_Color;

	texture_font_t* m_Font;
	texture_atlas_t* m_Atlas;

	void createFontAtlas(int width = 512, int height = 512, int depth = 1);
	 
public: 
	Font() {}
	Font(const std::string& fontName, const float& size, const unsigned int& color, bool create = true);
	~Font();

	void Init();
		
	void setColor(unsigned int color) {	m_Color = color; }
	void setSize(float size) { m_FontSize = size; }
	void setFont(std::string fontName) { m_FontName = fontName; }

	inline const std::string& getFontName() const { return m_FontName; }
	inline const float& getSize() const { return m_FontSize; }
	inline const unsigned int& getColor() const { return m_Color; }
	inline texture_atlas_t* getAtlas() const { return m_Atlas; }
	inline texture_font_t* getFont() const { return m_Font; }
};

} }

#endif