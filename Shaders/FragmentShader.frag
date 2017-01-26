#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 uv;
} fs_in;

uniform sampler2D tex;

void main()
{
	float intensity = 1.0 / length( fs_in.position.xy - light_pos ) * 0.5;
	color = intensity * fs_in.color;
	color = texture(tex, fs_in.uv) * intensity * fs_in.color;
} 