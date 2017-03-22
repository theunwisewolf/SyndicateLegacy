#include "Layer.h"

namespace Venus { namespace Graphics {

Layer::Layer(Renderer2D* renderer, Shader* shader, Maths::Matrix4 projectionMatrix)
	: m_Renderer(renderer),
	m_Shader(shader),
	m_ProjectionMatrix(projectionMatrix)
{
	this->m_Shader->enable();
	this->m_Shader->setUniformMat4("pr_matrix", this->m_ProjectionMatrix);
	this->m_Shader->disable();
}

void Layer::Add(Renderable2D* renderable)
{
	this->m_Renderables.push_back(renderable);
}

void Layer::Render()
{
	this->m_Shader->enable();
	this->m_Renderer->start();

	for (const Renderable2D* renderable : this->m_Renderables)
	{
		renderable->Submit(m_Renderer);
	}

	//this->m_Renderer->drawString("Hello World!", Maths::Vector2(-10.0f,0), nullptr, nullptr);

	this->m_Renderer->end();
	this->m_Renderer->flush();

	this->m_Shader->disable();
}

Layer::~Layer()
{
	delete this->m_Shader;
	delete this->m_Renderer;

	for (auto renderable : this->m_Renderables)
	{
		delete renderable;
	}

	this->m_Renderables.clear();
}

}}