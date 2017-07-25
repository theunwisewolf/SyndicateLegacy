#ifndef RENDERER2D_H_
#define RENDERER2D_H_

#include <Common.h>

#include <vector>
#include <string>
#include <GLM/vec2.hpp>
#include <GLM/mat4x4.hpp>
#include <freetype-gl.h>
#include <Systems/Graphics/Font.h>
#include <Systems/Graphics/Color.h>

namespace Syndicate { namespace Graphics { 

class SYNDICATE_API Renderable2D;

class SYNDICATE_API Renderer2D
{
protected:
	std::vector<glm::mat4> m_TransformationStack;
	const glm::mat4* m_TransformationBack;

	Renderer2D()
	{
		this->m_TransformationStack.push_back(glm::mat4(1.0f));
		this->m_TransformationBack = &this->m_TransformationStack.back();
	}

public:
	virtual ~Renderer2D() {};

	void push(const glm::mat4& matrix, bool override = false)
	{
		if (override)
			this->m_TransformationStack.push_back(matrix);
		else
			this->m_TransformationStack.push_back((*this->m_TransformationBack) * matrix);

		this->m_TransformationBack = &this->m_TransformationStack.back();
	}

	void pop()
	{
		if (this->m_TransformationStack.size() > 1) this->m_TransformationStack.pop_back();

		this->m_TransformationBack = &this->m_TransformationStack.back();
	}

	virtual void Start() {}
	virtual void Submit(const Renderable2D* renderable) = 0;
	virtual void DrawString(const std::string& text, glm::vec2 position, const Font& font) = 0;
	virtual void End() {}
	virtual void Render() = 0;
};

} }

#endif