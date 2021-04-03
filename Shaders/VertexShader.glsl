#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float time;


// Output value to fragment shader
out vec3 world_position;
out vec3 world_normal;
out vec3 normal;
out vec2 textcoord;
out vec3 position;

void main()
{
	
	world_position = (Model * vec4(v_position, 1)).xyz;
	world_normal = normalize(mat3(Model) * v_normal);
	position = v_position;
	
	textcoord = vec2(v_texture_coord.x - time * 0.1, v_texture_coord.y);
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
