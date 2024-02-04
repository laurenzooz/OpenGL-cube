#ifndef BUFFER_H
#define BUFFER_H
#include <GL/glew.h>


// Creates an opengl buffer object of given type
class Buffer
{
public:	
	GLuint id;
	GLint type;

	Buffer(GLint);

	void setData(int, const void*, GLuint usage = GL_STATIC_DRAW); 
	// sets the buffer data. Default usage is static draw


	void bind(); 	// binds the buffer
	void unbind(); 	// unbinds
};



#endif