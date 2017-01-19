#ifndef RENDERER2D_H_
#define RENDERER2D_H_

#define RENDERER2D_ERROR(x) std::cout << "Renderer2D Error: " << x << std::endl
#include <Systems/Graphics/Renderable2D.h>

namespace Venus { namespace Graphics { 

class Renderer2D
{
public:
	virtual void start() {}
	virtual void submit(const Renderable2D* renderable) = 0;
	virtual void end() {}
	virtual void flush() = 0;
};

} }

#endif