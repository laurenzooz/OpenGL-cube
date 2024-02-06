#version 460 core

layout(location = 0) in vec4 position;

uniform float time;
uniform vec3 coefficients; // randomized coefficients

out vec3 vertexColor;


void main()
{
	gl_Position = position;

	// Sine functions to create nice variation in color. Use the rand function for some coefficients
	vertexColor = vec3((0.5 * sin(time * coefficients[0]) + 0.5), (0.5 * sin(time * coefficients[1]) + 0.5), (0.5 * sin(time * coefficients[2]) + 0.5));
}



