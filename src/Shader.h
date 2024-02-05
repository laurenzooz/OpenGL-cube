#ifndef SHADER_H
#define SHADER_H

// Compiles a shader program when given a path to vertex shader and fragment shader
class Shader
{

public:

	Shader(std::string, std::string);
	GLuint id; // shader program id

private:
	std::string readFile(std::string&);
	
	GLuint compile(const char*, GLuint); // compiles the shader given the content of the file

	void getErrors(GLuint);



};



#endif