#ifndef BOX2D_DEBUG_DRAW_H_
#define BOX2D_DEBUG_DRAW_H_

#include <Common.h>
#include <Systems/Graphics/DebugDraw.h>

struct GLRenderTriangles;

class SYNDICATE_API Box2DDebugDraw : public DebugDraw
{
public:
	void Init();
	void End();
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);
};

#endif