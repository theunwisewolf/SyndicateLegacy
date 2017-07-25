/*
* Copyright (c) 2006-2013 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include <Common.h>
#include <GLM/mat4x4.hpp>

struct b2AABB;
struct GLRenderPoints;
struct GLRenderLines;
struct GLRenderTriangles;

struct GLRenderTriangles
{
	void Create(const glm::mat4& prMatrix);
	void Destroy();
	void Vertex(const b2Vec2& v, const b2Color& c);
	void Flush();

	enum { e_maxVertices = 3 * 512 };
	b2Vec2 m_vertices[e_maxVertices];
	b2Color m_colors[e_maxVertices];

	int32 m_count;

	GLuint m_vaoId;
	GLuint m_vboIds[2];
	GLuint m_programId;
	GLint m_projectionUniform;
	GLint m_vertexAttribute;
	GLint m_colorAttribute;

	void setPrMatrix(const glm::mat4& prMatrix)
	{
		this->m_PrMatrix = prMatrix;
	}

	glm::mat4 m_PrMatrix;
};

struct GLRenderLines
{
	void Create(const glm::mat4& prMatrix);
	void Destroy();
	void Vertex(const b2Vec2& v, const b2Color& c);
	void Flush();

	enum { e_maxVertices = 2 * 512 };
	b2Vec2 m_vertices[e_maxVertices];
	b2Color m_colors[e_maxVertices];

	int32 m_count;

	GLuint m_vaoId;
	GLuint m_vboIds[2];
	GLuint m_programId;
	GLint m_projectionUniform;
	GLint m_vertexAttribute;
	GLint m_colorAttribute;

	void setPrMatrix(const glm::mat4& prMatrix)
	{
		this->m_PrMatrix = prMatrix;
	}

	glm::mat4 m_PrMatrix;
};

//
struct SYNDICATE_API Camera
{
	Camera()
	{
		m_center.Set(0.0f, 0.0f);
		m_zoom = 12.0f;
		m_width = 960;
		m_height = 540;
	}

	b2Vec2 ConvertScreenToWorld(const b2Vec2& screenPoint);
	b2Vec2 ConvertWorldToScreen(const b2Vec2& worldPoint);
	void BuildProjectionMatrix(float32* m, float32 zBias);

	b2Vec2 m_center;
	float32 m_zoom;
	int32 m_width;
	int32 m_height;
};

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class SYNDICATE_API DebugDraw : public b2Draw
{
public:
	DebugDraw();
	~DebugDraw();

	void Create();
	void Destroy();

	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;

	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override;

	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override;

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override;

	void DrawTransform(const b2Transform& xf) override;

	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override;

	void DrawString(int x, int y, const char* string, ...); 

	void DrawString(const b2Vec2& p, const char* string, ...);

	void DrawAABB(b2AABB* aabb, const b2Color& color);

	void Flush();

	const glm::mat4& getPrMatrix() const { return this->m_PrMatrix; }

	void setPrMatrix(const glm::mat4& prMatrix)
	{
		this->m_PrMatrix = prMatrix;
		this->m_lines->setPrMatrix(prMatrix);
		this->m_triangles->setPrMatrix(prMatrix);
	}

	glm::mat4 m_PrMatrix;

protected:
	GLRenderPoints* m_points;
	GLRenderLines* m_lines;
	GLRenderTriangles* m_triangles;
};

extern DebugDraw g_debugDraw;
extern Camera g_camera;

#endif
