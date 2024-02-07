#version 460 core

layout(location = 0) in vec4 position;

// Model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * position;

}



