#include "Plane.h"

Plane::Plane(float size)
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

	// Unbind everything for now
	VAO.unbind();
	VBO.unbind();
	EBO.unbind();
	
}


void Plane::setVertices()
{
	float d = size / 2.0f; // the delta value of how much to be moved from origin
	vertices = 
	{//	 x, y,  z
		-d, 0, -d,
		 d, 0, -d,
		-d,	0,  d,
		 d,	0,  d,
	};
}


void Plane::draw()
{
	VAO.bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

