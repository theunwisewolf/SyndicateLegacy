#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_

#include <map>
#include <string>
#include <vector>
#include <freetype-gl.h>
#include <Utilities/File.h>

namespace Venus { namespace Graphics {

class FontManager
{
	// Name => Texture Font
	static std::map<std::string, texture_font_t*> m_FontCache;
	static std::map<std::string, std::string> m_FontDataCache;

public:
	static void loadFont(const std::string& fontName, const std::string& fontPath);
	static texture_font_t* getFont(std::string fontName, texture_atlas_t* atlas, float size);
	static void deleteFont(std::string fontName);
	FontManager();
	~FontManager();
};

}}

#endif