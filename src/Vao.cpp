#include "Vao.h"


Vao::Vao()
{
	glGenVertexArrays(1, &id);
}

void Vao::bind()
{
	glBindVertexArray(id);
}

void Vao::unbind()
{
	glBindVertexArray(0);
}
