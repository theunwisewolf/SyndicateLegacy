#ifndef SIMPLE_RENDERER2D_H_
#define SIMPLE_RENDERER2D_H_

#include <deque>
#include <Systems/Graphics/StaticSprite.h>
#include <Systems/Graphics/Renderer2D.h>
#include <Utilities/Maths/Maths.h>

namespace Venus { namespace Graphics {

class SimpleRenderer2D : public Renderer2D
{
private:
	std::deque<const StaticSprite*> m_RenderQueue;

public:
	void submit(const Renderable2D* renderable);
	void flush();
};

} }

#endif