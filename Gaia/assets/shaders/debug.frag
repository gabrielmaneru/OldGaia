#version 430 core
in vec2 v_pos;

layout(location=0) out vec4 fb_color;


void main()
{
	fb_color = vec4(v_pos, 0.0, 1.0);
}