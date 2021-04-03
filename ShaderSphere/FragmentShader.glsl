#version 330

// TODO: get values from fragment shader
in vec3 frag_position;
in vec3 frag_color;
in vec2 frag_textureCoord;
in vec3 frag_normal;


layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_textureCoord;
layout(location = 3) out vec4 out_position;

void main()
{
	out_color = vec4(frag_color, 1);
}