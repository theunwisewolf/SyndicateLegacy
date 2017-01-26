#ifndef SPRITE_H_
#define SPRITE_H_

#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <Systems/Graphics/Texture.h>

namespace Venus { namespace Graphics {

class Sprite : public Renderable2D
{
public:
	Sprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color);
	Sprite(Maths::Vector3 position, Maths::Vector2 size, Texture* texture);
	~Sprite();
};

} }

#endif