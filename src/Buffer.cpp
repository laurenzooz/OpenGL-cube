#include "Buffer.h"
#include <iostream>

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
	//this->bind(); // the buffer needs to be bind to set the data
	//std::cout << data[0];
	glBufferData(type, data.size() * sizeof(float), data.data(), usage);
	//this->unbind();
}

void Buffer::setData(std::vector <unsigned int> &data, GLuint usage)
{
	//this->bind(); // the buffer needs to be bind to set the data
	std::cout << data[0] << data[1] << data[2];
	std::cout << "data size: " << data.size() << " " << data.size() * sizeof(unsigned int);
	std::cout << type;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), usage);
	//this->unbind();
}

void Buffer::bind()
{
	if (type == GL_ELEMENT_ARRAY_BUFFER) std::cout << "stemmar";
	glBindBuffer(type, id);
}

void Buffer::unbind()
{
	glBindBuffer(type, 0);
}


