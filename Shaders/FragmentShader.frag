#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 uv;
	float tid;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0f / length( fs_in.position.xy - light_pos ) * 0.5f;
	vec4 texColor = fs_in.color;

	if( fs_in.tid > 0.0f )
	{
		int tid = int(fs_in.tid - 0.5f);
		texColor = texture(textures[tid], fs_in.uv);
	}	

	color = texColor;//vec4(0,1,0,1);//texColor * intensity; // texture(textures[int(fs_in.tid)], fs_in.uv) * intensity;
} 