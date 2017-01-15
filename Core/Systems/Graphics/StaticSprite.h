#ifndef STATIC_SPRITE_H_
#define STATIC_SPRITE_H_

#include <Systems/Graphics/Renderable2D.h>
#include <Utilities/Maths/Maths.h>

namespace Venus { namespace Graphics {

class StaticSprite : public Renderable2D
{
private: 
	Shader& m_Shader;
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;

public:
	StaticSprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color, Shader shader);
	~StaticSprite();

	inline Shader& getShader() const { return this->m_Shader; }

	inline const VertexArray* getVAO() const { return this->m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return this->m_IndexBuffer; }
};

} }

#endif