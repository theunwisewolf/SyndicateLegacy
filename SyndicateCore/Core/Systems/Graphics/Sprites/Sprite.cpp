#include "Sprite.h"

namespace Syndicate { namespace Graphics {

Sprite::Sprite(Maths::Vector3 position, Maths::Vector2 size, Color color)
	: Renderable2D(position, size, color)
{
	this->m_Texture = nullptr;
}

Sprite::Sprite(Maths::Vector3 position, Maths::Vector2 size, const std::string& texturePath)
	: Renderable2D(position, size, Color(0xffffffff))
{
	this->m_Texture = ResourceManager::i()->getTexture(texturePath);
}

Sprite::Sprite(Maths::Vector3 position, Maths::Vector2 size, Texture* texture)
	: Renderable2D(position, size, Color(0xffffffff))
{
	this->m_Texture = texture;
	this->m_bDeleteTexture = true;
}

Sprite::~Sprite()
{
	if (this->m_bDeleteTexture)
	{
		delete this->m_Texture;
		this->m_Texture = nullptr;
	}
}

}}