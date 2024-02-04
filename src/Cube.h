#ifndef CUBE_H
#define CUBE_H

// creates a cube of given size (length of one face). Creates and binds the vbo and ebo related to the cube, and sets the layout (vertex attribute pointers)
class Cube
{
private:
	float size; 
	glm::vec3 color;


	Buffer VBO, EBO;

	float* vertices(); // returns an array with the vertices with positions calculated depending on the cube size




public:
	Cube(float size = 0.5, glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f)); // size 0.5 by default. Color red by default.

};



#endif