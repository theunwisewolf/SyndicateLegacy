#ifndef RENDERABLE2D_H_
#define RENDERABLE2D_H_

#include <Common.h>

#include <Systems/Graphics/Color.h>

#include <Systems/Graphics/Buffers/Buffer.h>
#include <Systems/Graphics/Buffers/IndexBuffer.h>
#include <Systems/Graphics/Buffers/VertexArray.h>
#include <Systems/Graphics/Shader.h>

#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Systems/Graphics/Texture.h>

#include <Utilities/Maths/Maths.h>
 
namespace Syndicate { namespace Graphics { 


struct VertexData {
	Maths::Vector3 vertex;
	unsigned int color;
	Maths::Vector2 uv;
	float tid;
};

class SYNDICATE_API Renderable2D {
private:
	Maths::Vector2 m_Size;
	Maths::Vector3 m_Position;
	Color m_Color;
	std::vector<Maths::Vector2> m_UV;

protected:
	Texture* m_Texture;
	Position e_PositionParameter;

protected:
	Renderable2D() : m_Color(Color(0xffffffff)) { setDefaultUVs(); }

public:
	Renderable2D(Maths::Vector3 position, Maths::Vector2 size, Color color) :
		m_Position{position},
		m_Color{color},
		m_Size{size}
	{
		this->e_PositionParameter = Position::LEFT;
		setDefaultUVs();
	}

	Renderable2D(Position position, Maths::Vector2 size, Color color) :
		m_Color{ color },
		m_Size{ size }
	{
		this->e_PositionParameter = position;
		setDefaultUVs();
		ReAlign();
	}

	virtual ~Renderable2D() {}
	virtual void Submit(Renderer2D* renderer) const
	{
		renderer->Submit(this);
	}

	virtual void ReAlign()
	{
		switch (e_PositionParameter)
		{
		case Position::CENTER:
			m_Position = Maths::Vector3(-(m_Size.x / 2.0f), -(m_Size.y / 2.0f), 0.0f);
			break;
		case Position::LEFT:
			m_Position = Maths::Vector3(0.0f, 0.0f, 0.0f);
			break;
		case Position::RIGHT:
			m_Position = Maths::Vector3(m_Size.x, 0.0f, 0.0f);
			break;
		}
	}

	void setColor(const Color& color)								{ this->m_Color = color; }
	void setSize(const Maths::Vector2& size)						{ this->m_Size = size; }
	void setPosition(const Maths::Vector3& position)				{ this->m_Position = position; }

	inline const Maths::Vector2& getSize() const					{ return this->m_Size; }
	inline const Maths::Vector3& getPosition() const				{ return this->m_Position; }
	inline const Color& getColor() const							{ return this->m_Color; }
	inline const std::vector<Maths::Vector2>& getUVs() const		{ return this->m_UV; }

	inline Texture* getTexture() const								{ return this->m_Texture == nullptr ? 0 : this->m_Texture; }

private:
	void setDefaultUVs()
	{
		this->m_UV.push_back(Maths::Vector2(0, 0));
		this->m_UV.push_back(Maths::Vector2(0, 1));
		this->m_UV.push_back(Maths::Vector2(1, 1));
		this->m_UV.push_back(Maths::Vector2(1, 0));
	}
};


} }

#endif