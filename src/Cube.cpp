#include <glm/vec3.hpp>
#include <array>
#include <GL/glew.h>

#include "Buffer.h"
#include "Cube.h"

/*
	 7		    8
	  +---------+
 	 /         /|
	+--------+  |
	|3      4|  + 6
	|		 | /
	|        |/
	+--------+
	1		2


	Middle of the cube at origin. So each corner is 0.5*size to some direction
	Indices for the ebo would be 123, 234, 246, 468, 135, 357, 567, 678, 347, 478, 125, 256
	*/

Cube::Cube(float size = 0.5, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f))
{
	this->size = size;
	this->color = color;

	// set up the indices matrix
	unsigned int indices[36] = 
	{
		1, 2, 3, 
		2, 3, 4, 
		2, 4, 6,
		4, 6, 8, 
		1, 3, 5, 
		3, 5, 7,
		5, 6, 7, 
		6, 7, 8,
		3, 4, 7,
		4, 7, 8, 
		1, 2, 5,
		2, 5, 6
	};
	// set the EBO type, and then set the buffer data
	EBO.setType(GL_ELEMENT_ARRAY_BUFFER);
	EBO.setData(36, (void *) indices);
	VBO.setData(24, vertices());
}


float* Cube::vertices()
{
	float d = size / 2.0f; // the delta value of how much to be moved from origin

	float vertices[24] = 
	{//	   X 			Y 			Z
		0.0f - d,  	0.0f - d,  	0.0f - d,
		0.0f + d, 	0.0f - d, 	0.0f - d,
		0.0f + d, 	0.0f + d, 	0.0f - d,
		0.0f - d, 	0.0f + d, 	0.0f - d,

		0.0f - d, 	0.0f - d, 	0.0f + d,
		0.0f + d, 	0.0f - d, 	0.0f + d,
		0.0f + d, 	0.0f + d, 	0.0f + d,
		0.0f - d, 	0.0f + d, 	0.0f + d

	};

	return vertices;

}