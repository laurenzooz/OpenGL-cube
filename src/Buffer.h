#ifndef BUFFER_H
#define BUFFER_H


// Creates an opengl buffer object of given type
class Buffer
{
private:
	GLuint id;
	GLint type = GL_ARRAY_BUFFER;

public:	
	
	Buffer();

	void setType(GLint); // type is gl array buffer by default, but it can be changed with this
	void setData(int, const void*, GLuint usage = GL_STATIC_DRAW); 
	// sets the buffer data. Default usage is static draw


	void bind(); 	// binds the buffer
	void unbind(); 	// unbinds
};



#endif