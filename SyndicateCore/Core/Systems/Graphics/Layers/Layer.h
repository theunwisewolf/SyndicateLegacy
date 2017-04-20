#ifndef LAYER_H_
#define LAYER_H_

#include <Common.h>

#include <vector>
#include <map>
#include <string>

#include <Utilities/Maths/Maths.h>
#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Systems/Graphics/Sprites/Renderable2D.h>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API Layer
{
private:
	unsigned int m_ChildrenCount = 0;
	bool m_Freed;

protected:
	Shader* m_Shader;
	Renderer2D* m_Renderer;
	Maths::Matrix4 m_ProjectionMatrix;
	std::vector<Renderable2D*> m_Renderables;
	std::map<std::string, int> m_ChildrenMap;

public:
	Layer();
	Layer(Renderer2D* renderer, Shader* shader, Maths::Matrix4 projectionMatrix);

	void SetShader(Shader* shader) { this->m_Shader = shader; }
	void SetRenderer(Renderer2D* renderer) { this->m_Renderer = renderer; }
	void SetProjectionMatrix(Maths::Matrix4 pr_matrix);

	virtual ~Layer();

	virtual unsigned int Add(Renderable2D* renderable);
	virtual void Add(std::string name, Renderable2D* renderable);
	virtual void Render();
	virtual void Free(); // Frees all sprites, resources, explicitly

	Renderable2D* GetSprite(std::string name);
	Renderable2D* GetSprite(int index);

	unsigned int getChildrenCount() const { return this->m_ChildrenCount; }
};

}}

#endif