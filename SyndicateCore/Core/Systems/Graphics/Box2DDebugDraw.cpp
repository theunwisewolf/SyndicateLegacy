#include "Box2DDebugDraw.h"

void Box2DDebugDraw::Init()
{
	this->Create();
}

void Box2DDebugDraw::End()
{
	this->Destroy();
}

void Box2DDebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	std::cout << "DrawPolygon was called" << std::endl;
}
void Box2DDebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
	b2Color fillColor(0.5f * color.r, 0.5f * color.g, 0.5f * color.b, 0.5f);

	for (int32 i = 1; i < vertexCount - 1; ++i)
	{
		m_triangles->Vertex(vertices[0], fillColor);
		m_triangles->Vertex(vertices[i], fillColor);
		m_triangles->Vertex(vertices[i + 1], fillColor);
	}

	b2Vec2 p1 = vertices[vertexCount - 1];
	for (int32 i = 0; i < vertexCount; ++i)
	{
		b2Vec2 p2 = vertices[i];
		m_lines->Vertex(p1, color);
		m_lines->Vertex(p2, color);
		p1 = p2;
	}

	this->Flush();
	//GLfloat glverts[16]; //allow for polygons up to 8 vertices
	//glVertexPointer(2, GL_FLOAT, 0, glverts); //tell OpenGL where to find vertices
	//glEnableClientState(GL_VERTEX_ARRAY); //use vertices in subsequent calls to glDrawArrays

	////fill in vertex positions as directed by Box2D
	//for (int i = 0; i < vertexCount; i++) {
	//	glverts[i * 2] = vertices[i].x;
	//	glverts[i * 2 + 1] = vertices[i].y;
	//}

	////draw solid area
	//glColor4f(color.r, color.g, color.b, 1);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	////draw lines
	//glLineWidth(1); //fat lines
	//glColor4f(1, 0, 1, 1); //purple
	//glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
}
void Box2DDebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	std::cout << "DrawCircle was called" << std::endl;
}
void Box2DDebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	std::cout << "DrawSolidCircle was called" << std::endl;
}
void Box2DDebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	std::cout << "DrawSegment was called" << std::endl;
}
void Box2DDebugDraw::DrawTransform(const b2Transform& xf)
{
	std::cout << "DrawTransform was called" << std::endl;
}