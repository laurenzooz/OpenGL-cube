#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <vector>

#include "Buffer.h"
#include "Vao.h"


// creates a cube of given size (length of one face). Creates and binds the vbo and ebo related to the cube, and sets the layout (vertex attribute pointers)
class Cube
{
public:
	Cube(float size = 0.5, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f)); // size 0.5 by default. Color red by default.

	void draw(); // draws the cube

	glm::vec3 color;
	
private:
	float size; 
	
	std::vector<float> vertices; // data for the vertices


	Buffer VBO, EBO;
	Vao VAO;

	// indices to draw the triangles to make the cube (for ebo)
	std::vector<unsigned int> indices = 
	{
		0, 1, 2, 
		1, 2, 3,
		1, 3, 5,
		3, 5, 7,
		0, 2, 4,
		2, 4, 6,
		4, 5, 6,
		5, 6, 7,
		2, 3, 6,
		3, 6, 7,
		0, 1, 4,
		1, 4, 5
	};

	void setVertices(); // returns an array with the vertices with positions calculated depending on the cube size

};



#endif