#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <Common.h>

#include <tuple>
#include <vector>
#include <GL/glew.h>
#include <Systems/Graphics/Shader.h>
#include <Utilities/Maths/Maths.h>

#define rgb(r,g,b) Maths::Vector4(r/255.0f, g/255.0f, b/255.0f, 1.0f)
#define rgba(r,g,b,a) Maths::Vector4(r/255.0f, g/255.0f, b/255.0f, a/255.0f)
#define normalize_color(x) x/255.0f

namespace Venus {
	namespace Graphics {

using namespace Maths;

enum class DRAW_TYPE {
	DRAW_ARRAYS, DRAW_ELEMENTS
};

class Graphics2D
{
private:
	std::vector<std::tuple<GLuint, DRAW_TYPE, Shader>> polygons;

public:
	Graphics2D();

	std::tuple<GLuint, DRAW_TYPE, Shader> DrawTriangle(const Vector3& bottomLeft, const Vector3& top, const Vector3& bottomRight, Shader shader, Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f), bool normalize = true);
	std::tuple<GLuint, DRAW_TYPE, Shader> DrawRectangle(const Vector3& bottomLeft, const Vector3& topLeft, const Vector3& topRight, const Vector3& bottomRight, Shader shader, Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f), bool normalize = true);
	
	void Draw(std::tuple<GLuint, DRAW_TYPE, Shader> polygon);
	Maths::Vector4 normalizeColors(Maths::Vector4 color);
	~Graphics2D();
};

	}
}

#endif