#ifndef SIMPLE_RENDERER2D_H_
#define SIMPLE_RENDERER2D_H_

#include <Common.h>

#include <deque>
#include <Systems/Graphics/Sprites/StaticSprite.h>
#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Utilities/Maths/Maths.h>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API SimpleRenderer2D : public Renderer2D
{
private:
	std::deque<const StaticSprite*> m_RenderQueue;

public:
	void Submit(const Renderable2D* renderable) override;
	void Render() override;
};

} }

#endif