#version 440 core
layout (location = 0) in vec3  a_position;
layout (location = 1) in vec3  a_normal;
layout (location = 2) in vec2  a_uv;
layout (location = 3) in vec3  a_tangent;
layout (location = 4) in vec3  a_bitangent;
layout (location = 5) in vec4  a_wbones;
layout (location = 6) in ivec4 a_bones;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec4 v_color;

void main()
{
	v_color = vec4(a_position, 1.0);
	gl_Position = P*V*M*vec4(a_position, 1.0);
}