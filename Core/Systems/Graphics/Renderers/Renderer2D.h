#ifndef RENDERER2D_H_
#define RENDERER2D_H_

#include <vector>
#include <string>
#include <Utilities/Maths/Maths.h>
#include <freetype-gl.h>

#define RENDERER2D_ERROR(x) std::cout << "Renderer2D Error: " << x << std::endl

namespace Venus { namespace Graphics { 

class Renderable2D;

class Renderer2D
{
protected:
	std::vector<Maths::Matrix4> m_TransformationStack;
	const Maths::Matrix4* m_TransformationBack;

	Renderer2D()
	{
		this->m_TransformationStack.push_back(Maths::Matrix4::Identity());
		this->m_TransformationBack = &this->m_TransformationStack.back();
	}

public:
	void push(const Maths::Matrix4& matrix, bool override = false)
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

	virtual void start() {}
	virtual void submit(const Renderable2D* renderable) = 0;
	virtual void drawString(const std::string& text, Maths::Vector2 position, texture_atlas_t* atlas, texture_font_t* font) = 0;
	virtual void end() {}
	virtual void flush() = 0;
};

} }

#endif