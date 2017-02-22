#include "BatchRenderer2D.h"

namespace Venus { namespace Graphics {

void BatchRenderer2D::start()
{
	this->m_RendererStarted = true;

	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	this->m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BatchRenderer2D::submit(const Renderable2D* renderable)
{
	if (this->m_RendererStarted == false)
	{
		RENDERER2D_ERROR("Renderer2D was not started using the start() method. Starting internally.");
		this->start();
	}

	const Maths::Vector2& size = renderable->getSize();
	const Maths::Vector3& position = renderable->getPosition();
	const Maths::Vector4& color = renderable->getColor();
	const std::vector<Maths::Vector2>& uv = renderable->getUVs();
	const GLuint textureID = renderable->getTextureID();
	unsigned int c = 0;
	
	float ts = 0.0f;
	if (textureID)
	{
		bool found = false;
		for (unsigned int i = 0; i < this->m_TextureSlots.size(); ++i)
		{
			if (this->m_TextureSlots[i] == textureID)
			{
				found = true;
				ts = (float)(i+1);
				break;
			}
		}

		if (!found)
		{
			if (this->m_TextureSlots.size() >= 32)
			{
				this->end();
				this->flush();
				this->start();
			}

			this->m_TextureSlots.push_back(textureID);
			ts = (float)this->m_TextureSlots.size();
		}
	}
	else
	{
		// We are not going to use normalized colors
		int r = color.x;
		int g = color.y;
		int b = color.z;
		int a = color.w;

		c = a << 24 | b << 16 | g << 8 | r;
	}

	this->m_Buffer->vertex = *this->m_TransformationBack * position;
	this->m_Buffer->color  = c;
	this->m_Buffer->uv = uv[0];
	this->m_Buffer->tid = ts;
	this->m_Buffer++;

	this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(position.x, position.y + size.y, 0);
	this->m_Buffer->color = c;
	this->m_Buffer->uv = uv[1];
	this->m_Buffer->tid = ts;
	this->m_Buffer++;

	this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(position.x + size.x, position.y + size.y, 0);
	this->m_Buffer->color = c;
	this->m_Buffer->uv = uv[2];
	this->m_Buffer->tid = ts;
	this->m_Buffer++;

	this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(position.x + size.x, position.y, 0);
	this->m_Buffer->color = c;
	this->m_Buffer->uv = uv[3];
	this->m_Buffer->tid = ts;
	this->m_Buffer++;

	this->m_IndexCount += 6;
}

void BatchRenderer2D::end()
{
	this->m_RendererStarted = false;

	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchRenderer2D::flush()
{
	if (this->m_RendererStarted == true)
	{
		RENDERER2D_ERROR("Renderer2D was not ended using the end() method. Ending internally.");
		this->end();
	}

	for (int i = 0; i < this->m_TextureSlots.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, this->m_TextureSlots[i]);
	}

	glBindVertexArray(this->m_VAO);
	this->m_IBO->Bind();

	glDrawElements(GL_TRIANGLES, this->m_IndexCount, GL_UNSIGNED_INT, nullptr);

	this->m_IBO->Unbind();
	glBindVertexArray(0);

	this->m_IndexCount = 0;
}

BatchRenderer2D::BatchRenderer2D()
{
	this->m_RendererStarted = false;

	glGenVertexArrays(1, &this->m_VAO);
	glGenBuffers(1, &this->m_VBO);
	
	glBindVertexArray(this->m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
	glBufferData(GL_ARRAY_BUFFER, RENDERER2D_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	// Enable our vertex attribute arrays
	glEnableVertexAttribArray(SHADER_VERTEX_POSITION_LOCATION);
	glEnableVertexAttribArray(SHADER_VERTEX_COLOR_LOCATION);
	glEnableVertexAttribArray(SHADER_VERTEX_UV_LOCATION);
	glEnableVertexAttribArray(SHADER_VERTEX_TID_LOCATION);

	// Set all the values for the vertices
	glVertexAttribPointer(SHADER_VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)0);
	glVertexAttribPointer(SHADER_VERTEX_COLOR_LOCATION, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color));
	glVertexAttribPointer(SHADER_VERTEX_UV_LOCATION, 2, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::uv));
	glVertexAttribPointer(SHADER_VERTEX_TID_LOCATION, 1, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint *indices = new GLuint[RENDERER2D_INDICES_SIZE];

	int offset = 0;
	for (int i = 0; i < RENDERER2D_INDICES_SIZE; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	this->m_IBO = new IndexBuffer(indices, RENDERER2D_INDICES_SIZE);

	glBindVertexArray(0);
}

BatchRenderer2D::~BatchRenderer2D()
{
	delete this->m_IBO;
	glDeleteBuffers(1, &this->m_VBO);
}

}}