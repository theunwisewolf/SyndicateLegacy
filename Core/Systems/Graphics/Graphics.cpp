#include "Graphics.h"

namespace Venus { namespace Graphics {

Graphics2D::Graphics2D()
{
}

std::tuple<GLuint, DRAW_TYPE, Shader> Graphics2D::DrawTriangle(const Vector3 & bottomLeft, const Vector3 & top, const Vector3 & bottomRight, Shader shader, Vector4 color, bool normalize)
{
	GLuint vao, vbo;
	GLfloat vertices[] = {
		bottomLeft.x, bottomLeft.y, bottomLeft.z,
		top.x, top.y, top.z,
		bottomRight.x, bottomRight.y, bottomRight.z,
	};

	if (normalize)
	{
		color = this->normalizeColors(color);
	}

	// Enable alpha blending if alpha channel isn't 1
	glDisable(GL_BLEND);
	if (color.w != 1.0f)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	shader.enable();
	shader.setUniform4f("fcolor", color);
	shader.disable();

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		GLuint posAttrib = glGetAttribLocation(shader.getShaderID(), "position");

		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(GLfloat)), (GLvoid*)0);

	glBindVertexArray(0);

	auto polygon = std::forward_as_tuple(vao, DRAW_TYPE::DRAW_ARRAYS, shader);
	this->polygons.push_back(polygon);

	return polygon;
}

std::tuple<GLuint, DRAW_TYPE, Shader> Graphics2D::DrawRectangle(const Vector3 & bottomLeft, const Vector3 & topLeft, const Vector3 & topRight, const Vector3 & bottomRight, Shader shader, Vector4 color, bool normalize)
{
	GLuint vao, vbo, ebo;
	GLfloat vertices[] = {
		bottomLeft.x, bottomLeft.y, bottomLeft.z,
		topLeft.x, topLeft.y, topLeft.z,
		topRight.x, topRight.y, topRight.z, 
		bottomRight.x, bottomRight.y, bottomRight.z,
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	if (normalize)
	{
		color = this->normalizeColors(color);
	}

	// Enable alpha blending if alpha channel isn't 1
	glDisable(GL_BLEND);
	if (color.w != 1.0f)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	shader.enable();
	shader.setUniform4f("fcolor", color);
	shader.disable();

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		GLuint posAttrib = glGetAttribLocation(shader.getShaderID(), "position");

		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(GLfloat)), (GLvoid*)0);

	glBindVertexArray(0);

	auto polygon = std::forward_as_tuple(vao, DRAW_TYPE::DRAW_ELEMENTS, shader);
	this->polygons.push_back(polygon);

	return polygon;
}

void Graphics2D::Draw(std::tuple<GLuint, DRAW_TYPE, Shader> polygon)
{
	Shader shader;
	GLuint vao;
	DRAW_TYPE drawType;

	std::tie(vao, drawType, shader) = polygon;

	shader.enable();
	glBindVertexArray(vao);

	switch (drawType)
	{
	case DRAW_TYPE::DRAW_ARRAYS:   glDrawArrays(GL_TRIANGLES, 0, 3);	
	break;
	case DRAW_TYPE::DRAW_ELEMENTS: glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	break;
	}

	glBindVertexArray(0);
	shader.disable();
}

Maths::Vector4 Graphics2D::normalizeColors(Maths::Vector4 color)
{
	color.x = normalize_color(color.x);
	color.y = normalize_color(color.y);
	color.z = normalize_color(color.z);

	return color;
}

Graphics2D::~Graphics2D()
{
	// Delete all shaders, vertex array objects
	for (auto polygon : this->polygons)
	{
		std::get<2>(polygon).disable();
		glDeleteVertexArrays(1, &std::get<0>(polygon));
		glDeleteProgram(std::get<2>(polygon).getShaderID());
	}
}

}}