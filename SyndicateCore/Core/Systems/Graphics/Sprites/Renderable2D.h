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

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>
 
namespace Syndicate { namespace Graphics { 

struct VertexData {
	glm::vec3 vertex;
	unsigned int color;
	glm::vec2 uv;
	float tid;
};

class SYNDICATE_API Renderable2D {
private:
	glm::vec2 m_Size;
	glm::vec3 m_Scale;
	glm::vec3 m_Position;
	float m_Angle;
	Color m_Color;
	std::vector<glm::vec2> m_UV;

protected:
	Texture* m_Texture;
	Position e_PositionParameter;

protected:
	Renderable2D() : m_Color(Color(0xffffffff)), m_Angle(0.0f) { setDefaultUVs(); }

public:
	Renderable2D(glm::vec3 position, glm::vec2 size, Color color) :
		m_Position{position},
		m_Color{color},
		m_Size{size},
		m_Scale(1.0f, 1.0f, 1.0f),
		m_Angle(0.0f)
	{
		this->e_PositionParameter = Position::LEFT;
		setDefaultUVs();
	}

	Renderable2D(Position position, glm::vec2 size, Color color) :
		m_Color{ color },
		m_Size{ size },
		m_Scale(1.0f, 1.0f, 1.0f),
		m_Angle(0.0f)
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
			m_Position = glm::vec3(-(m_Size.x / 2.0f), -(m_Size.y / 2.0f), 0.0f);
			break;
		case Position::LEFT:
			m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
			break;
		case Position::RIGHT:
			m_Position = glm::vec3(m_Size.x, 0.0f, 0.0f);
			break;
		}
	}

	// Sets the Color of the sprite
	void setColor(const Color& color)						{ this->m_Color = color; }

	// Sets the Size of the sprite
	void setSize(const glm::vec2& size)						{ this->m_Size = size;	 }

	// Sets the Scale factor of the sprite
	void setSize(const glm::vec3& scale)					{ this->m_Scale = scale; }

	// Sets the Position of the sprite
	void setPosition(const glm::vec3& position)				{ this->m_Position = position; }

	// Sets the Angle of the sprite
	void setAngle(float angle)								{ this->m_Angle = angle; }

	inline const glm::vec2& getSize() const					{ return this->m_Size; }
	inline const glm::vec3& getScale() const				{ return this->m_Scale; }
	inline const glm::vec3& getPosition() const				{ return this->m_Position; }
	inline const Color& getColor() const					{ return this->m_Color; }
	inline const std::vector<glm::vec2>& getUVs() const		{ return this->m_UV; }

	// Angle in degrees
	inline const float& getAngle() const					{ return this->m_Angle; }

	inline Texture* getTexture() const						{ return this->m_Texture == nullptr ? 0 : this->m_Texture; }

	// Rotates a vertex by angle (degrees)
	inline glm::vec2 rotatePoint(glm::vec2 point, float angle) const
	{
		glm::vec2 newPoint;

		angle = Maths::Math::toRadians(angle);

		newPoint.x = point.x * cos(angle) - point.y * sin(angle);
		newPoint.y = point.x * sin(angle) + point.y * cos(angle);

		return newPoint;
	}

private:
	void setDefaultUVs()
	{
		this->m_UV.push_back(glm::vec2(0, 0));
		this->m_UV.push_back(glm::vec2(0, 1));
		this->m_UV.push_back(glm::vec2(1, 1));
		this->m_UV.push_back(glm::vec2(1, 0));
	}
};


} }

#endif