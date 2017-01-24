#include "SimpleRenderer2D.h"
#include <Systems/Graphics/Sprites/Renderable2D.h>

namespace Venus { namespace Graphics {

void SimpleRenderer2D::flush()
{
	while (this->m_RenderQueue.empty() == false)
	{
		const StaticSprite* sprite = this->m_RenderQueue.front();

		sprite->getVAO()->Bind();
		sprite->getIBO()->Bind();

		//sprite->getShader().enable();
		//sprite->getShader().setUniformMat4("ml_matrix", Maths::Matrix4::Translation( renderable->getPosition() ));
		glDrawElements(GL_TRIANGLES, sprite->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);
		//sprite->getShader().disable();

		sprite->getIBO()->Unbind();
		sprite->getVAO()->Unbind();

		this->m_RenderQueue.pop_front();
	}
}

void SimpleRenderer2D::submit(const Renderable2D* renderable)
{
	this->m_RenderQueue.push_back((StaticSprite*)renderable);
}

} }