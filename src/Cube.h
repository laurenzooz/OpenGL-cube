#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <vector>

#include "Buffer.h"
#include "Vao.h"


// creates a default, untextured cube of given size (length of one face). Creates and binds the vbo and ebo related to the cube, and sets the layout (vertex attribute pointers)
class Cube
{
public:
	Cube(float size = 0.5); // size 0.5 by default. Color red by default.

	void draw(); // draws the cube
	
protected:
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

// Cube that has texture position and normals stored in the vertices
class TexturedCube : public Cube
{
public:
	TexturedCube(float size = 0.5);

	void setVertices();
private:
	// need more vertices to get the texture and normals set properly
	std::vector<unsigned int> indices = 
	{
		0, 1, 2, 
		1, 2, 3,

		4, 5, 6,
		5, 6, 7,

		8, 9, 10,
		9, 10, 11,

		12, 13, 14, 
		13, 14, 15,

		16, 17, 18,
		17, 18, 19,

		20, 21, 22,
		21, 22, 23

		


	};
};

#endif