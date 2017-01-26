#include "Sprite.h"

namespace Venus { namespace Graphics {

Sprite::Sprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color)
	: Renderable2D(position, size, color)
{
	this->m_Texture = nullptr;
}

Sprite::Sprite(Maths::Vector3 position, Maths::Vector2 size, Texture* texture)
	: Renderable2D(position, size, Maths::Vector4(1,0,0,1))
{
	this->m_Texture = texture;
}

Sprite::~Sprite()
{
}

}}