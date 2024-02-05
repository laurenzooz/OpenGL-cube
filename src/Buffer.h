#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>
#include <vector>

// Creates an opengl buffer object of given type
class Buffer
{
private:
	GLuint id;
	GLint type = GL_ARRAY_BUFFER;

public:	
	
	Buffer();

	void setType(GLint); // type is gl array buffer by default, but it can be changed with this
	void setData(std::vector<float>&, GLuint usage = GL_STATIC_DRAW); 
	void setData(std::vector<unsigned int>&, GLuint usage = GL_STATIC_DRAW); 
	// sets the buffer data. Default usage is static draw, Overload to use with int data too (for ebos)


	void bind(); 	// binds the buffer
	void unbind(); 	// unbinds
};



#endif