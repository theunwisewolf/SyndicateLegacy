#ifndef FONT_MANAGER_H_
#define FONT_MANAGER_H_

#include <map>
#include <string>
#include <vector>
#include <freetype-gl.h>
#include <Utilities/File.h>

#define ATLAS_WIDTH		512
#define ATLAS_HEIGHT	512
#define ATLAS_BIT_DEPTH 1

namespace Venus { namespace Graphics {

class FontManager
{
	// Name => Texture Font
	static std::map<std::string, texture_font_t*> m_FontCache;
	static std::map<std::string, std::string> m_FontDataCache;

public:
	static void loadFont(const std::string& fontName, const std::string& fontPath);
	static texture_font_t* getFont(std::string fontName, float size);
	static void deleteFont(std::string fontName);
	static void Clear();
};

}}

#endif