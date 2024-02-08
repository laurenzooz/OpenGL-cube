#version 460 core

layout(location = 0) in vec4 position_a;
layout(location = 1) in vec2 texturePos_a;
layout(location = 2) in vec3 normal_a;

uniform float time;

// Model, view and projection matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 color;
uniform bool colorVariation; // use the color variation over time or not

out vec3 vertexColor;
out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

void main()
{

	// Multiply the position of the vertex by the matrices
	// Cube's local coordinates -> world coordinates -> coordinates in respect to the camera -> screen coordinates
	gl_Position = projection * view * model * position_a;

	if (colorVariation)
		// Sine functions to create nice variation in color.
		vertexColor = vec3((0.5 * sin(time * 1.2) + 0.5), (0.5 * sin(time * 0.7) + 0.5), (0.5 * sin(time * 0.4) + 0.5));
	else
		vertexColor = color;

	texCoord = texturePos_a;

	// Calculate fragment positions
	fragPos = vec3(model * position_a); 	

	// transpose inverse to maintain the normals perpendicular even if cube turns or moves
	normal = normalize(mat3(transpose(inverse(model))) * normal_a);
}



