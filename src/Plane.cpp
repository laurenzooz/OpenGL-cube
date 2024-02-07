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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (float*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (float*)(5 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Unbind everything for now
	VAO.unbind();
	VBO.unbind();
	EBO.unbind();
	
}


void Plane::setVertices()
{
	float d = size / 2.0f; // the delta value of how much to be moved from origin
	vertices = 
	{//	 x, y,  z,     t,    s,   n.x, n.y, n.z
		-d, 0.0f, -d, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
		 d, 0.0f, -d, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-d,	0.0f,  d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 d,	0.0f,  d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f
	};
}


void Plane::draw()
{
	VAO.bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

