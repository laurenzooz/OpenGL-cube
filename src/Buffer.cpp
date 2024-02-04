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

void Buffer::setData(int size, const void* data, GLuint usage = GL_STATIC_DRAW)
{
	this->bind(); // the buffer needs to be bind to set the data
	glBufferData(type, size, data, GL_STATIC_DRAW);
	this->unbind();
}

void Buffer::bind()
{
	glBindBuffer(type, id);
}

void Buffer::unbind()
{
	glBindBuffer(type, 0);
}


