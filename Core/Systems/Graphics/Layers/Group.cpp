#include "Group.h"

namespace Venus { namespace Graphics { 

Group::Group(const Maths::Matrix4& transform)
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

void Group::Add(Renderable2D* sprite)
{
	this->m_Sprites.push_back(sprite);
}

Group::~Group()
{
	for (auto renderable : m_Sprites)
	{
		delete renderable;
	}
}

} }