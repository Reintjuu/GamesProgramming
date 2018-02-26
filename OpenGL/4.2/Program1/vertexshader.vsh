#version 430 core

in vec4 position;
in vec4 color;

out vec4 vColor;

void main()
{
	gl_Position = position;
	vColor = color;
}