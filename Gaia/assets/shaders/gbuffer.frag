#version 440 core
layout (location = 0) in vec3  v_position;
layout (location = 1) in vec2  v_uv;
layout (location = 2) in vec3  v_tangent;
layout (location = 3) in vec3  v_bitangent;
layout (location = 4) in vec3  v_normal;

layout (binding = 0) uniform sampler2D albedo_txt;
layout (binding = 1) uniform sampler2D metallic_txt;
layout (binding = 2) uniform sampler2D roughness_txt;
layout (binding = 3) uniform sampler2D normal_txt;

uniform bool active_albedo_txt;
uniform bool active_metallic_txt;
uniform bool active_roughness_txt;
uniform bool active_normal_txt;

uniform vec3 albedo_color;
uniform float metallic_value;
uniform float roughness_value;

layout (location = 0) out vec3  fb_position;
layout (location = 1) out vec3  fb_albedo;
layout (location = 2) out vec2  fb_metallic_roughness;
layout (location = 3) out vec3  fb_normal;

void main()
{
	vec3 albedo;
	if(active_albedo_txt)
	{
		vec4 color = texture(albedo_txt, v_uv);
		if(color.a < 0.5)
			discard;
		albedo = color.rgb;
	}
	else
		albedo = albedo_color;

	float metallic;
	if(active_metallic_txt)
		metallic = texture(metallic_txt, v_uv).r;
	else
		metallic = metallic_value;

	float roughness;
	if(active_roughness_txt)
		roughness = texture(roughness_txt, v_uv).r;
	else
		roughness = roughness_value;

	vec3 normal;
	if(active_normal_txt)
	{
		vec3 T = normalize(v_tangent);
		vec3 B = normalize(v_bitangent);
		vec3 N = normalize(v_normal);
		vec3 normal_txt_value = 2.0 * texture(normal_txt, v_uv).xyz - 1.0;
		normal = normalize(mat3(T,B,N) * normal_txt_value);
	}
	else
		normal = normalize(v_normal);

	fb_position = v_position;
	fb_albedo = albedo;
	fb_metallic_roughness = vec2(metallic, roughness);
	fb_metallic_roughness = v_uv;
	fb_normal = normal;
}