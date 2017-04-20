#include "BatchRenderer2D.h"

namespace Syndicate { namespace Graphics {

void BatchRenderer2D::Start()
{
	this->m_RendererStarted = true;

	GL(glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO));
	this->m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

float BatchRenderer2D::GetTexture(Texture* texture)
{
	float textureSlot = 0.0f;

	bool found = false;
	for (unsigned int i = 0; i < this->m_Textures.size(); ++i)
	{
		if (this->m_Textures[i] == texture)
		{
			found = true;
			textureSlot = (float)(i + 1);
			break;
		}
	}

	if (!found)
	{
		if (this->m_Textures.size() >= 32)
		{
			this->End();
			this->Render();
			this->Start();
		}

		this->m_Textures.push_back(texture);
		textureSlot = (float)this->m_Textures.size();
	}

	return textureSlot;
}

void BatchRenderer2D::Submit(const Renderable2D* renderable)
{
	if (this->m_RendererStarted == false)
	{
		SYNDICATE_WARNING("Renderer2D was not started using the start() method. Starting internally.");
		this->Start();
	}

	const Maths::Vector2& size = renderable->getSize();
	const Maths::Vector3& position = renderable->getPosition();
	const Color& color = renderable->getColor();
	const std::vector<Maths::Vector2>& uv = renderable->getUVs();
	const Texture* texture = renderable->getTexture();
	unsigned int c = 0;
	
	float textureSlot = 0.0f;
	if (texture)
	{
		textureSlot = this->GetTexture(renderable->getTexture());
	}
	else
	{
		// We are not going to use normalized colors
		c = color.Pack();
	}

	this->m_Buffer->vertex = *this->m_TransformationBack * position;
	this->m_Buffer->color  = c;
	this->m_Buffer->uv = uv[0];
	this->m_Buffer->tid = textureSlot;
	this->m_Buffer++;

	this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(position.x, position.y + size.y, 0);
	this->m_Buffer->color = c;
	this->m_Buffer->uv = uv[1];
	this->m_Buffer->tid = textureSlot;
	this->m_Buffer++;

	this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(position.x + size.x, position.y + size.y, 0);
	this->m_Buffer->color = c;
	this->m_Buffer->uv = uv[2];
	this->m_Buffer->tid = textureSlot;
	this->m_Buffer++;
	
	this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(position.x + size.x, position.y, 0);
	this->m_Buffer->color = c;
	this->m_Buffer->uv = uv[3];
	this->m_Buffer->tid = textureSlot;
	this->m_Buffer++;

	this->m_IndexCount += 6;
}

void BatchRenderer2D::DrawString(const std::string& text, Maths::Vector2 position, const Font& font)
{
	if (this->m_RendererStarted == false)
	{
		SYNDICATE_WARNING("Renderer2D was not started using the start() method. Starting internally.");
		this->Start();
	}

	unsigned int c = 0;

	float textureSlot = this->GetTexture(font.getTexture());
	Texture* texture = font.getTexture();
	int textureID = texture->GetTextureID();

	// We are not going to use normalized colors
	c = font.getColor().Pack();
	
	float scaleX = Font::getScale().x;
	float scaleY = Font::getScale().y;
	
	float x = position.x;

	for (int i = 0; i < text.length(); ++i)
	{
		texture_glyph_t* glyph = texture_font_get_glyph(font.getFont(), &text[i]);

		if (glyph)
		{
			float kerning = 0.0f;

			if (i > 0)
			{
				kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
				x += kerning / scaleX;
			}

			float x0 = x + glyph->offset_x / scaleX;
			float y0 = position.y + glyph->offset_y / scaleY;
			float x1 = x0 + glyph->width / scaleX;
			float y1 = y0 - glyph->height / scaleY;

			float u0 = glyph->s0;
			float v0 = glyph->t0;
			float u1 = glyph->s1;
			float v1 = glyph->t1;

			this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(x0, y0, 0);
			this->m_Buffer->color = c;
			this->m_Buffer->uv = Maths::Vector2(u0, v0);
			this->m_Buffer->tid = textureSlot;
			this->m_Buffer++;

			this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(x0, y1, 0);
			this->m_Buffer->color = c;
			this->m_Buffer->uv = Maths::Vector2(u0, v1);
			this->m_Buffer->tid = textureSlot;
			this->m_Buffer++;

			this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(x1, y1, 0);
			this->m_Buffer->color = c;
			this->m_Buffer->uv = Maths::Vector2(u1, v1);
			this->m_Buffer->tid = textureSlot;
			this->m_Buffer++;

			this->m_Buffer->vertex = *this->m_TransformationBack * Maths::Vector3(x1, y0, 0);
			this->m_Buffer->color = c;
			this->m_Buffer->uv = Maths::Vector2(u1, v0);
			this->m_Buffer->tid = textureSlot;
			this->m_Buffer++;

			this->m_IndexCount += 6;
			
			x += glyph->advance_x / scaleX;
		}
	}

	// Look in cache
	// We only update the texture if the text has changed
	auto it = m_TextureAtlasCache.find(textureID);

	// Found
	if (it != m_TextureAtlasCache.end() && it->second == text)
	{
		return;
	}

	m_TextureAtlasCache.emplace(textureID, text);

	// Bind the OpenGL Texture
	texture->Bind();
	texture->SetData(font.getAtlas()->data);
}

void BatchRenderer2D::End()
{
	this->m_RendererStarted = false;

	GL(glUnmapBuffer(GL_ARRAY_BUFFER));
	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void BatchRenderer2D::Render()
{
	if (this->m_RendererStarted == true)
	{
		SYNDICATE_WARNING("Renderer2D was not ended using the end() method. Ending internally.");
		this->End();
	}

	for (int i = 0; i < this->m_Textures.size(); ++i)
	{
		GL(glActiveTexture(GL_TEXTURE0 + i));
		GL(glBindTexture(GL_TEXTURE_2D, this->m_Textures[i]->GetTextureID()));
	}

	GL(glBindVertexArray(this->m_VAO));
	this->m_IBO->Bind();

	GL(glDrawElements(GL_TRIANGLES, this->m_IndexCount, GL_UNSIGNED_INT, nullptr));

	this->m_IBO->Unbind();
	GL(glBindVertexArray(0));

	this->m_IndexCount = 0;
}

BatchRenderer2D::BatchRenderer2D()
	: m_IndexCount(0)
{
	this->m_RendererStarted = false;

	GL(glGenVertexArrays(1, &this->m_VAO));
	GL(glGenBuffers(1, &this->m_VBO));
	
	GL(glBindVertexArray(this->m_VAO));
	GL(glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO));
	GL(glBufferData(GL_ARRAY_BUFFER, RENDERER2D_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW));

	// Enable our vertex attribute arrays
	GL(glEnableVertexAttribArray(SHADER_VERTEX_POSITION_LOCATION));
	GL(glEnableVertexAttribArray(SHADER_VERTEX_COLOR_LOCATION));
	GL(glEnableVertexAttribArray(SHADER_VERTEX_UV_LOCATION));
	GL(glEnableVertexAttribArray(SHADER_VERTEX_TID_LOCATION));

	// Set all the values for the vertices
	GL(glVertexAttribPointer(SHADER_VERTEX_POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)0));
	GL(glVertexAttribPointer(SHADER_VERTEX_COLOR_LOCATION, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::color)));
	GL(glVertexAttribPointer(SHADER_VERTEX_UV_LOCATION, 2, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::uv)));
	GL(glVertexAttribPointer(SHADER_VERTEX_TID_LOCATION, 1, GL_FLOAT, GL_FALSE, RENDERER2D_VERTEX_SIZE, (const GLvoid*)offsetof(VertexData, VertexData::tid)));

	GL(glBindBuffer(GL_ARRAY_BUFFER, 0));

	unsigned int *indices = synnew unsigned int[RENDERER2D_INDICES_SIZE];

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

	this->m_IBO = synnew IndexBuffer(indices, RENDERER2D_INDICES_SIZE);
	delete[] indices;

	GL(glBindVertexArray(0));
}

BatchRenderer2D::~BatchRenderer2D()
{
	delete this->m_IBO;
	GL(glDeleteBuffers(1, &this->m_VBO));
}

}}