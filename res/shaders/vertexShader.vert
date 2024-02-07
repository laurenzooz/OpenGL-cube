#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texturePos;

uniform float time;
uniform vec3 coefficients; // randomized coefficients

// Model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;
out vec2 texCoord;

void main()
{
	// Multiply the position of the vertex by the matrices
	// Cube's local coordinates -> world coordinates -> coordinates in respect to the camera -> screen coordinates
	gl_Position = projection * view * model * position;

	// Sine functions to create nice variation in color.
	vertexColor = vec3((0.5 * sin(time * coefficients[0]) + 0.5), (0.5 * sin(time * coefficients[1]) + 0.5), (0.5 * sin(time * coefficients[2]) + 0.5));

	texCoord = texturePos;

}



