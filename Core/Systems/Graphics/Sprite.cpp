#include "Sprite.h"

namespace Venus { namespace Graphics {

Sprite::Sprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color)
	: Renderable2D(position, size, color)
{
}

Sprite::~Sprite()
{
}

}}