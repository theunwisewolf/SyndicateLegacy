#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

out DATA
{
	vec4 position;
	vec4 color;
	vec2 uv;
} vs_out;

void main()
{
	vs_out.position = ml_matrix * vec4(position, 1.0);
	vs_out.color = color;
	vs_out.uv = uv;

	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(position.x, position.y, position.z, 1.0);
}