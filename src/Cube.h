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
private:
	float size; 
	glm::vec3 color;

	std::vector<float> vertices; // data for the vertices


	Buffer VBO, EBO;
	Vao VAO;

	// indices to draw the triangles to make the cube (for ebo)
	std::vector<unsigned int> indices = 
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

	void setVertices(); // returns an array with the vertices with positions calculated depending on the cube size




public:
	Cube(float size = 0.5, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f)); // size 0.5 by default. Color red by default.

	void draw(); // draws the cube

};



#endif