#ifndef STATIC_SPRITE_H_
#define STATIC_SPRITE_H_

#include <Common.h>

#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <Systems/Graphics/Texture.h>
#include <Utilities/Maths/Maths.h>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API StaticSprite : public Renderable2D
{
private: 
	Shader& m_Shader;
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;

public:
	StaticSprite(Maths::Vector3 position, Maths::Vector2 size, Maths::Vector4 color, Shader shader);
	StaticSprite(Maths::Vector3 position, Maths::Vector2 size, Texture* texture, Shader shader);
	~StaticSprite();

	inline Shader& getShader() const { return this->m_Shader; }

	inline const VertexArray* getVAO() const { return this->m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return this->m_IndexBuffer; }
};

} }

#endif