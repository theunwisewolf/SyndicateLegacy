#ifndef SPRITE_H_
#define SPRITE_H_

#include <Common.h>

#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <Systems/ResourceManager.h>

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API Sprite : public Renderable2D
{
private:
	bool m_bDeleteTexture = false;
public:
	Sprite(glm::vec3 position, glm::vec2 size, Color color);
	Sprite(glm::vec3 position, glm::vec2 size, const std::string& texturePath);
	Sprite(glm::vec3 position, glm::vec2 size, Texture* texture);

	Sprite(Position position, glm::vec2 size, Color color);
	Sprite(Position position, glm::vec2 size, const std::string& texturePath);
	Sprite(Position position, glm::vec2 size, Texture* texture);
	~Sprite();
};

} }

#endif