#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texturePos;
layout(location = 2) in vec3 normal;

// Model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexNormal;
out vec3 eyePos;

void main()
{
	eyePos = vec3(model * position); 

	gl_Position = projection * view * model * position;

	vertexNormal = normal;

}



