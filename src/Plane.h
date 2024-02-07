#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

#include <vector>

#include "Buffer.h"
#include "Vao.h"


// creates a flat, square plane
class Plane
{
public:
	Plane(float size = 1.0);

	void draw(); // draws the plane
	
protected:
	float size; 
	
	std::vector<float> vertices; // data for the vertices


	Buffer VBO, EBO;
	Vao VAO;

	// indices to draw the triangles to make the plane
	std::vector<unsigned int> indices = 
	{
		0, 1, 2, 
		1, 2, 3,
	};

	void setVertices(); // returns an array with the vertices with positions calculated depending on the cube size

};


#endif