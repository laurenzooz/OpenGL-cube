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

void Buffer::setData(std::vector <float> &data, GLuint usage)
{
	glBufferData(type, data.size() * sizeof(float), data.data(), usage);
}

void Buffer::setData(std::vector <unsigned int> &data, GLuint usage)
{
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), usage);
}

void Buffer::bind()
{
	glBindBuffer(type, id);
}

void Buffer::unbind()
{
	glBindBuffer(type, 0);
}


