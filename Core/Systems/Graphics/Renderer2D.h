#ifndef RENDERER2D_H_
#define RENDERER2D_H_

#include <Systems/Graphics/Renderable2D.h>

namespace Venus { namespace Graphics { 

class Renderer2D
{
public:
	virtual void submit(const Renderable2D* renderable) = 0;
	virtual void flush() = 0;
};

} }

#endif