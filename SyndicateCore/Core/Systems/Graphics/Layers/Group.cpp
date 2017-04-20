#include "Group.h"

namespace Syndicate { namespace Graphics { 

Group::Group(const Maths::Matrix4& transform) :
	m_ChildrenCount(0)
{
	this->m_TransformationMatrix = transform;
}

void Group::Submit(Renderer2D* renderer) const
{
	renderer->push(this->m_TransformationMatrix);

	for (const Renderable2D* sprite : this->m_Sprites)
	{
		sprite->Submit(renderer);
	}

	renderer->pop();
}

void Group::Add(std::string name, Renderable2D* sprite)
{
	int index = this->Add(sprite);
	this->m_ChildrenMap.emplace(name, index);
}

unsigned int Group::Add(Renderable2D* sprite)
{
	this->m_ChildrenCount++;
	this->m_Sprites.push_back(sprite);

	return this->m_ChildrenCount - 1;
}

Renderable2D* Group::GetSprite(int index)
{
	if (index < this->m_ChildrenCount)
	{
		return this->m_Sprites[index];
	}
}

Renderable2D* Group::GetSprite(std::string name)
{
	// We only load the texture if it's not found in the cache
	auto it = this->m_ChildrenMap.find(name);

	// Not found
	if (it == this->m_ChildrenMap.end())
	{
		return nullptr;
	}

	return this->m_Sprites[it->second];
}

Group::~Group()
{
	for (auto renderable : m_Sprites)
	{
		delete renderable;
	}
}

} }