#version 330 core

layout(location = 0) in vec4 position;

uniform vec3 color;
out vec3 vertexColor;

void main()
{
	gl_Position = position;
	vertexColor = color;
}



