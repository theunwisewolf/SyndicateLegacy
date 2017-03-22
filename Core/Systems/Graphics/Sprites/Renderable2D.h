#ifndef RENDERABLE2D_H_
#define RENDERABLE2D_H_

#include <Systems/Graphics/Buffers/Buffer.h>
#include <Systems/Graphics/Buffers/IndexBuffer.h>
#include <Systems/Graphics/Buffers/VertexArray.h>
#include <Systems/Graphics/Shader.h>

#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Systems/Graphics/Texture.h>

#include <Utilities/Maths/Maths.h>
 
namespace Venus { namespace Graphics { 

struct VertexData {
	Maths::Vector3 vertex;
	GLuint color;
	Maths::Vector2 uv;
	float tid;
};

class Renderable2D {
private:
	Maths::Vector2 m_Size;
	Maths::Vector3 m_Position;
	Maths::Vector4 m_Color;
	std::vector<Maths::Vector2> m_UV;

protected:
	Texture* m_Texture;

protected:
	Renderable2D() { setDefaultUVs(); }

public:
	Renderable2D(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color) :
		m_Position{position},
		m_Color{color},
		m_Size{size}
	{
		setDefaultUVs();
	}

	virtual ~Renderable2D() {}
	virtual void Submit(Renderer2D* renderer) const
	{
		renderer->submit(this);
	}

	inline const Maths::Vector2& getSize() const					{ return this->m_Size; }
	inline const Maths::Vector3& getPosition() const				{ return this->m_Position; }
	inline const Maths::Vector4& getColor() const					{ return this->m_Color; }
	inline const std::vector<Maths::Vector2>& getUVs() const		{ return this->m_UV; }

	inline const GLuint& getTextureID() const						{ return this->m_Texture == nullptr ? 0 : this->m_Texture->getTextureID(); }

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