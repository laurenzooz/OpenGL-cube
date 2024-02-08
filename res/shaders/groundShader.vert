#version 460 core

layout(location = 0) in vec4 position_a;
layout(location = 1) in vec2 texturePos_a;
layout(location = 2) in vec3 normal_a;

// Model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragPos;


void main()
{

	gl_Position = projection * view * model * position_a;

	fragPos = vec3(model * position_a); 
	normal = normalize(mat3(transpose(inverse(model))) * normal_a);

}



