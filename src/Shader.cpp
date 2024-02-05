#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

Shader::Shader(std::string pathVertex, std::string pathFragment)
{
	// create the shader program
	id = glCreateProgram(); 

	// read and save the contents of the shaders
	std::string vertexSource = readFile(pathVertex);
	std::string fragmentSource = readFile(pathFragment);

	// Convert to const char and compile the shaders
	const char* source = vertexSource.c_str();
	GLuint vertexShader = compile(source, GL_VERTEX_SHADER);

	source = fragmentSource.c_str();
	GLuint fragmentShader = compile(source, GL_FRAGMENT_SHADER);

	
	// attach shaders to the shader program
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);

	// Link and check for errors
	glLinkProgram(id);

	GLint result;
	glGetShaderiv(id, GL_LINK_STATUS, &result);

	if (result == GL_FALSE) getErrors(id);

	// Delete as these are now unnecessary
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


std::string Shader::readFile(std::string& path)
{
	std::ifstream f;
    f.open(path); // open the file

	

    std::stringstream s;
    s << f.rdbuf(); // read the file
    std::string shaderString = s.str(); // create a string that holds the content of the file

	f.close(); 


	return shaderString;
}


GLuint Shader::compile(const char* source, GLuint type)
{	
	// Create the shader and get the id
	GLuint shaderId = glCreateShader(type);
	
	// attach the source
	glShaderSource(shaderId, 1, &source, NULL); 

	// Compile the shader, check for errors, if not any, return the compiled shader id
	glCompileShader(shaderId);


	// check for possible shader compile errors
	GLint result;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		getErrors(shaderId);
		return 0;
	}

	return shaderId;
}



void Shader::getErrors(GLuint id)
{
	char message[1024];
	glGetShaderInfoLog(id, 1024, NULL, message);
	std::cout << "Error!\n" <<  message << std::endl; // print the errors
}
