#ifndef LAYER_H_
#define LAYER_H_

#include <Common.h>

#include <vector>

#include <Utilities/Maths/Maths.h>
#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Systems/Graphics/Sprites/Renderable2D.h>

namespace Venus { namespace Graphics {

class Layer
{
protected:
	Shader* m_Shader;
	Renderer2D* m_Renderer;
	Maths::Matrix4 m_ProjectionMatrix;
	std::vector<Renderable2D*> m_Renderables;

protected:
	Layer(Renderer2D* renderer, Shader* shader, Maths::Matrix4 projectionMatrix);

public:
	virtual ~Layer();

	virtual void Add(Renderable2D* renderable);
	virtual void Render();
};

}}

#endif