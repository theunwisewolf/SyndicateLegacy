#ifndef RENDERABLE2D_H_
#define RENDERABLE2D_H_

#include <Systems/Graphics/Buffers/Buffer.h>
#include <Systems/Graphics/Buffers/IndexBuffer.h>
#include <Systems/Graphics/Buffers/VertexArray.h>
#include <Systems/Graphics/Shader.h>

#include <Utilities/Maths/Maths.h>

namespace Venus { namespace Graphics { 

struct VertexData {
	Maths::Vector3 vertex;
	Maths::Vector4 color;
};

class Renderable2D {
private:
	Maths::Vector2 m_Size;
	Maths::Vector3 m_Position;
	Maths::Vector4 m_Color;

public:
	Renderable2D(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color) :
		m_Position{position},
		m_Color{color},
		m_Size{size}
	{
		
	}

	virtual ~Renderable2D() {}

public:
	inline const Maths::Vector2& getSize() const { return this->m_Size; }
	inline const Maths::Vector3& getPosition() const { return this->m_Position; }
	inline const Maths::Vector4& getColor() const { return this->m_Color; }
};

} }

#endif