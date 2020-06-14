#version 430 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 attr_norm;
layout (location = 2) in vec2 attr_uvs;
layout (location = 3) in vec3 attr_tan;
layout (location = 4) in vec3 attr_bit;
layout (location = 5) in vec4 attr_wbones;
layout (location = 6) in ivec4 attr_bones;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec4 v_color;

void main()
{
	v_color = vec4(a_position, 1.0);
	gl_Position = P*V*M*vec4(a_position, 1.0);
}