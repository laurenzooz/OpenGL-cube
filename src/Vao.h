#ifndef VAO_H
#define VAO_H

// Creates an opengl vertex array object
class Vao
{
public:	
	
	Vao();

	void bind();
	void unbind(); 	

private:
	GLuint id;
};
#endif