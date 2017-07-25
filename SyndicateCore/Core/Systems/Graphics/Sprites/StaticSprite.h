#ifndef STATIC_SPRITE_H_
#define STATIC_SPRITE_H_

#include <Common.h>

#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <Systems/Graphics/Texture.h>

#include <GLM/vec2.hpp>
#include <GLM/vec3.hpp>
#include <GLM/vec4.hpp>

namespace Syndicate { namespace Graphics {

class SYNDICATE_API StaticSprite : public Renderable2D
{
private: 
	Shader& m_Shader;
	VertexArray* m_VertexArray;
	IndexBuffer* m_IndexBuffer;

public:
	StaticSprite(glm::vec3 position, glm::vec2 size, Color color, Shader shader);
	StaticSprite(glm::vec3 position, glm::vec2 size, Texture* texture, Shader shader);
	~StaticSprite();

	inline Shader& getShader() const { return this->m_Shader; }

	inline const VertexArray* getVAO() const { return this->m_VertexArray; }
	inline const IndexBuffer* getIBO() const { return this->m_IndexBuffer; }
};

} }

#endif