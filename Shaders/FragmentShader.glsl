#version 330

uniform sampler2D texture_1;
uniform float contor;

// TODO: get color value from vertex shader
in vec3 normal;
in vec2 textcoord;
in vec3 world_position;
in vec3 world_normal;
in vec3 position;


// Uniforms for light properties
uniform float light_position[200];
uniform float light_direction[200];
uniform float light_position_allien[200];
uniform float light_direction_allien[200];

uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform float angle;
uniform vec3 object_color;


layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;

float CalcPointLight(vec3 lightPos, vec3 lightDir, int type)
{
	
	vec3 L = normalize(lightPos - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);

	float diffuse =  material_kd * max(dot(normalize(world_normal), L), 0);

	float specular = 0;
	if(diffuse > 0) {
		specular = material_ks * pow(max(dot(normalize(world_normal), L), 0), material_shininess);
	}

	float result = 0;
	int check = 0;

	if(type == 1) {
		float cut_off = radians(angle);
		float spot_light = dot(-L, lightDir);
		float spot_light_limit	= cos(cut_off);

		if (spot_light >  spot_light_limit)
		{
			check = 1;
			float linear_att = (spot_light - spot_light_limit) / (1 - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			result = light_att_factor * (diffuse + specular);
		}
	}

	if(check == 0) {
		float dis = distance(lightPos, position);
		float attenuation_factor = 1 / (1 + dis * dis);
		result = attenuation_factor * (diffuse + specular);
	}

    return 3 * result;
} 
 
void main()
{
	float light = 0;
	for(int i = 0; i < 200; i += 3) {
		if(light_position[i] != -99999) {
			vec3 current_light_pos = vec3(light_position[i], light_position[i + 1], light_position[i + 2]);
			vec3 current_light_dir = vec3(light_direction[i], light_direction[i + 1], light_direction[i + 2]);
			
			light += CalcPointLight(current_light_pos, current_light_dir, 0);
		}
	}

	for(int i = 0; i < 200; i += 3) {
		if(light_position_allien[i] != -99999) {
			vec3 current_allien_pos = vec3(light_position_allien[i], light_position_allien[i + 1], light_position_allien[i + 2]);
			vec3 current_allien_dir = vec3(light_direction_allien[i], light_direction_allien[i + 1], light_direction_allien[i + 2]);
			
			light += CalcPointLight(current_allien_pos, current_allien_dir, 1);
		}
	}


	light += 0.3;	 
	if(contor == 1) {
		vec4 inter = texture2D(texture_1, textcoord);
		vec3 aux = vec3(inter.x, inter.y, inter.z);
		out_color = vec4(aux * light, inter.a);

		if (out_color.a == 0)
		{
			discard;
		}
	} else {
		out_color = vec4(object_color * light, 1);
	}

	out_normal = vec4(normal, 1);
}