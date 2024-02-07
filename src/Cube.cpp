#include "Cube.h"

/*
	 6		    7
	   --------- 
 	 /         /|
	 --------   |
	|2      3|    5
	|		 | /
	|        |/
	 -------- 
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
		-d, -d, -d,
		 d,	-d, -d,
		-d,	 d, -d,
		 d,	 d, -d,
		-d,	-d,  d,
		 d,	-d,  d,
		-d,	 d,  d,
		 d,	 d,  d

	};
}


void Cube::draw()
{
	VAO.bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}



/// Textured cube

// constructor slightly different as the vertex attrib array is different
TexturedCube::TexturedCube(float size)
{
	this->size = size;

	// set the EBO type, and then bind the VAO, VBO and EBO
	EBO.setType(GL_ELEMENT_ARRAY_BUFFER);

	VAO.bind();
	VBO.bind();
	EBO.bind();	
	

	// calculate vertex positions with given size of the cube
	setVertices();

	// set the buffer data	
	VBO.setData(vertices);
	EBO.setData(indices);

	// Set the layout and enable
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// unbind everything for now
	VAO.unbind();
	VBO.unbind();
	EBO.unbind();
	
}


// textured cube's vertices have also texture position and normals 
// need more vertices than normal cube to set the normals and tex positions correctly
void TexturedCube::setVertices()
{
	float d = size / 2.0f; // the delta value of how much to be moved from origin
	vertices = 
	{//	 X   Y	Z	 s	   t	 n.x   n.y	 n.z
	// Front face
		-d, -d, -d, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		 d, -d, -d, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
		-d,  d, -d, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
		 d,  d, -d, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,

	// Rear face
		 d, -d,  d, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-d, -d,  d, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 d,  d,  d, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-d,  d,  d, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,

	// Right face
		 d, -d, -d, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 d, -d,  d, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		 d,  d, -d, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		 d,  d,  d, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	// Left face
		-d, -d, -d, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-d, -d,  d, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-d,  d, -d, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-d,  d,  d, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

	// Top face
		-d, d, -d, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 d, d, -d, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-d, d,  d, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		 d, d,  d, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	// Bottom face
		-d, -d, -d, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		 d, -d, -d, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-d, -d,  d, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
		 d, -d,  d, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f	
	};
}