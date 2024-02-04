#include <glm/vec3.hpp>
#include <array>
#include <GL/glew.h>

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

Cube::Cube(float size, glm::vec3 color)
{
	this->size = size;
	this->color = color;

	// set the EBO type, and then bind the VAO, VBO and EBO
	EBO.setType(GL_ELEMENT_ARRAY_BUFFER);
	
	EBO.bind();
	VBO.bind();
	VAO.bind();


	

	// set the buffer data
	EBO.setData(36 * sizeof(int), (void *) indices);
	VBO.setData(24 * sizeof(float), vertices.data());

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	// unbind everything for now
	//VAO.unbind();
	//EBO.unbind();
	//VBO.unbind();
}

void Cube::setVertices()
{
	float d = size / 2.0f; // the delta value of how much to be moved from origin
	d = 0.8f;
	vertices = 
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

	//vertices = dataa;

}


void Cube::draw()
{
	VAO.bind();
	VBO.bind();
	EBO.bind();
	//glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_POINTS, 0, 24);
}