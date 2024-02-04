#ifndef VAO_H
#define VAO_H
#include <GL/glew.h>


// Creates an opengl vertex array object
class Vao
{
private:
	GLuint id;
	
public:	
	
	Vao();

	void bind();
	void unbind(); 	

};
#endif