#version 430 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 attr_norm;
layout (location = 2) in vec2 attr_uvs;
layout (location = 3) in vec3 attr_tan;
layout (location = 4) in vec3 attr_bit;
layout (location = 5) in vec4 attr_wbones;
layout (location = 6) in ivec4 attr_bones;

out vec4 v_color;

void main()
{
	v_color = vec4(attr_bit, 1.0);
	gl_Position = vec4(a_position, 1.0);
}