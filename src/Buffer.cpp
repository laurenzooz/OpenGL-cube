#include <GL/glew.h>

#include "Buffer.h"


// generates the buffer and saves the type of the buffer
Buffer::Buffer()
{
	glGenBuffers(1, &id);
}

void Buffer::setType(GLint type)
{
	this->type = type;
}

void Buffer::setData(int size, const void* data, GLuint usage)
{
	//this->bind(); // the buffer needs to be bind to set the data
	glBufferData(type, size, data, usage);
	//this->unbind();
}

void Buffer::bind()
{
	glBindBuffer(type, id);
}

void Buffer::unbind()
{
	glBindBuffer(type, 0);
}


