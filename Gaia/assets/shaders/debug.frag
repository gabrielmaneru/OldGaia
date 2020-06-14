#version 430 core
in vec4 v_color;

layout(location=0) out vec4 fb_color;


void main()
{
	fb_color = v_color;
}