#include "Sprite.h"

namespace Syndicate { namespace Graphics {

Sprite::Sprite(glm::vec3 position, glm::vec2 size, Color color)
	: Renderable2D(position, size, color)
{
	this->m_Texture = nullptr;
}

Sprite::Sprite(glm::vec3 position, glm::vec2 size, const std::string& identifier)
	: Renderable2D(position, size, Color(0xffffffff))
{
	this->m_Texture = ResourceManager::i()->getTexture(identifier);
}

Sprite::Sprite(glm::vec3 position, glm::vec2 size, Texture* texture)
	: Renderable2D(position, size, Color(0xffffffff))
{
	this->m_Texture = texture;
	this->m_bDeleteTexture = true;
}

Sprite::Sprite(Position position, glm::vec2 size, Color color)
	: Renderable2D(position, size, color)
{
	this->m_Texture = nullptr;
}

Sprite::Sprite(Position position, glm::vec2 size, const std::string& identifier)
	: Renderable2D(position, size, Color(0xffffffff))
{
	this->m_Texture = ResourceManager::i()->getTexture(identifier);
}

Sprite::Sprite(Position position, glm::vec2 size, Texture* texture)
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