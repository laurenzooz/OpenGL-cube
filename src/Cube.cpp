#include "Cube.h"

/*
	 6		    7
	  +---------+
 	 /         /|
	+--------+  |
	|2      3|  + 5
	|		 | /
	|        |/
	+--------+
	0		1


	Middle of the cube at origin. So each corner is 0.5*size to some direction
	*/

Cube::Cube(float size)
{
	this->size = size;

	// set the EBO type, and then bind the VAO, VBO and EBO
	EBO.setType(GL_ELEMENT_ARRAY_BUFFER);

	VAO.bind();
	VBO.bind();
	EBO.bind();	
	

	// calculate vertex positions with given size of the
	setVertices();


	// set the buffer data	
	VBO.setData(vertices);
	EBO.setData(indices);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// unbind everything for now
	VAO.unbind();
	VBO.unbind();
	EBO.unbind();
	
}


void Cube::setVertices()
{
	float d = size / 2.0f; // the delta value of how much to be moved from origin
	vertices = 
	{//	   X 			Y 			Z
		0.0f - d,  	0.0f - d,  	0.0f - d,
		0.0f + d, 	0.0f - d, 	0.0f - d,
		0.0f - d, 	0.0f + d, 	0.0f - d,
		0.0f + d, 	0.0f + d, 	0.0f - d,

		0.0f - d, 	0.0f - d, 	0.0f + d,
		0.0f + d, 	0.0f - d, 	0.0f + d,
		0.0f - d, 	0.0f + d, 	0.0f + d,
		0.0f + d, 	0.0f + d, 	0.0f + d

	};
}


void Cube::draw()
{
	VAO.bind();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}