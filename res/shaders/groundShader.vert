#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texturePos;
layout(location = 2) in vec3 normal;

// Model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;


out vec3 vertexNormal;
out vec3 lightDir;


void main()
{

	gl_Position = projection * view * model * position;

	vec3 eyePos = vec3(model * position); 
	lightDir = normalize(lightPos - eyePos);

	vertexNormal = normalize(mat3(transpose(inverse(model))) * normal);

}



