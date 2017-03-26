#ifndef SPRITE_H_
#define SPRITE_H_

#include <Common.h>

#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <Systems/ResourceManager.h>

namespace Venus { namespace Graphics {

class Sprite : public Renderable2D
{
private:
	bool m_bDeleteTexture = false;
public:
	Sprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color);
	Sprite(Maths::Vector3 position, Maths::Vector2 size, const std::string& texturePath);
	Sprite(Maths::Vector3 position, Maths::Vector2 size, Texture* texture);
	~Sprite();
};

} }

#endif