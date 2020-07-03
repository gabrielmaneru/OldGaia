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

layout (location = 0) out vec3  v_position;
layout (location = 1) out vec2  v_uv;
layout (location = 2) out vec3  v_tangent;
layout (location = 3) out vec3  v_bitangent;
layout (location = 4) out vec3  v_normal;

void main()
{
	mat4 MV = V*M;
	vec4 v_position4 = MV*vec4(a_position, 1.0);
	v_position = v_position4.xyz;
	gl_Position = P*v_position4;

	v_uv = a_uv;

	mat3 normal_mtx = inverse(transpose(mat3(MV)));
	v_tangent = normal_mtx * a_tangent;
	v_bitangent = normal_mtx * a_bitangent;
	v_normal = normal_mtx * a_normal;
}