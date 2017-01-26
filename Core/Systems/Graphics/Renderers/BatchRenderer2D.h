#ifndef BATCH_RENDERER2D_H
#define BATCH_RENDERER2D_H

#include <Systems/Graphics/Renderers/Renderer2D.h>
#include <Systems/Graphics/Sprites/Renderable2D.h>
#include <GL/glew.h>

#define SHADER_VERTEX_POSITION_LOCATION 0
#define SHADER_VERTEX_COLOR_LOCATION    1
#define SHADER_VERTEX_UV_LOCATION		2
#define SHADER_VERTEX_TID_LOCATION		3

#define RENDERER2D_MAX_SPRITES		60000
#define RENDERER2D_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER2D_SPRITE_SIZE		RENDERER2D_VERTEX_SIZE * 4
#define RENDERER2D_BUFFER_SIZE		RENDERER2D_SPRITE_SIZE * RENDERER2D_MAX_SPRITES
#define RENDERER2D_INDICES_SIZE		RENDERER2D_MAX_SPRITES * 6

namespace Venus { namespace Graphics {
	
class BatchRenderer2D : public Renderer2D
{
private:
	VertexData* m_Buffer;
	GLuint  m_VAO;
	GLuint  m_VBO;
	GLsizei m_IndexCount;
	IndexBuffer* m_IBO;

	bool m_RendererStarted;

	std::vector<GLuint> m_TextureSlots;

public:
	BatchRenderer2D();

	void start() override;
	void submit(const Renderable2D* renderable) override;
	void end() override;
	void flush() override;

	~BatchRenderer2D();
};

} }

#endif