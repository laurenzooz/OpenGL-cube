#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texturePos;

uniform float time;

// Model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 color;
uniform bool colorVariation; // use the color variation over time or not

out vec3 vertexColor;
out vec2 texCoord;


void main()
{
	// Multiply the position of the vertex by the matrices
	// Cube's local coordinates -> world coordinates -> coordinates in respect to the camera -> screen coordinates
	gl_Position = projection * view * model * position;

	if (colorVariation)
		// Sine functions to create nice variation in color.
		vertexColor = vec3((0.5 * sin(time * 1.2) + 0.5), (0.5 * sin(time * 0.7) + 0.5), (0.5 * sin(time * 0.4) + 0.5));
	else
		vertexColor = color;

	texCoord = texturePos;

}



