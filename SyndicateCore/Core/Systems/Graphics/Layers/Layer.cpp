#include "Layer.h"

namespace Syndicate { namespace Graphics {

Layer::Layer() : 
	m_ChildrenCount(0),
	m_Freed(false)
{

}

Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projectionMatrix) :
	m_Renderer(renderer),
	m_Shader(shader),
	m_ProjectionMatrix(projectionMatrix),
	m_ChildrenCount(0),
	m_Freed(false)
{
	this->m_Shader->Enable();
	this->m_Shader->setUniformMat4("pr_matrix", this->m_ProjectionMatrix);
	this->m_Shader->Disable();
}

void Layer::Add(std::string name, Renderable2D* renderable)
{
	int index = this->Add(renderable);
	m_ChildrenMap.emplace(name, index);
}

Renderable2D* Layer::GetSprite(int index)
{
	if (index < this->m_ChildrenCount)
	{
		return this->m_Renderables[index];
	}

	return nullptr;
}

Renderable2D* Layer::GetSprite(std::string name)
{
	// We only load the texture if it's not found in the cache
	auto it = this->m_ChildrenMap.find(name);

	// Not found
	if (it == this->m_ChildrenMap.end())
	{
		return nullptr;
	}

	return this->m_Renderables[it->second];
}

void Layer::SetProjectionMatrix(glm::mat4 pr_matrix)
{
	this->m_ProjectionMatrix = pr_matrix;

	this->m_Shader->Enable();
	this->m_Shader->setUniformMat4("pr_matrix", pr_matrix);
	this->m_Shader->Disable();
}


unsigned int Layer::Add(Renderable2D* renderable)
{
	this->m_ChildrenCount++;
	this->m_Renderables.push_back(renderable);

	return this->m_ChildrenCount - 1;
}

void Layer::Render()
{
	// We have nothing to render
	if (!this->m_Renderables.size())
	{
		return;
	}

	this->m_Shader->Enable();
	this->m_Renderer->Start();

	for (const Renderable2D* renderable : this->m_Renderables)
	{
		renderable->Submit(m_Renderer);
	}

	this->m_Renderer->End();
	this->m_Renderer->Render();

	this->m_Shader->Disable();
}

void Layer::Free()
{
	if (!m_Freed)
	{
		delete this->m_Shader;
		delete this->m_Renderer;

		for (auto renderable : this->m_Renderables)
		{
			delete renderable;
			renderable = nullptr;
		}

		this->m_Shader = nullptr;
		this->m_Renderer = nullptr;

		this->m_Renderables.clear();

		m_Freed = true;
	}
}

Layer::~Layer()
{
	// If no one has freed the resources, free them
	this->Free();
}

}}