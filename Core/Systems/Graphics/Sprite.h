#ifndef SPRITE_H_
#define SPRITE_H_

#include <Systems/Graphics/Renderable2D.h>

namespace Venus { namespace Graphics {

class Sprite : public Renderable2D
{
public:
	Sprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color);
	~Sprite();
};

} }

#endif