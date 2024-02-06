#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <random>
#include <algorithm>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Cube.h"
#include "Shader.h"

const unsigned int width = 640;
const unsigned int height = 480;

float randomFloat() 
{
	float num = ((float) rand()) / (float) RAND_MAX;
    return num;

}

int main()
{
	srand(time(0));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create window and initialize glfw
	GLFWwindow* window;
	if (!glfwInit()) 
	{
		std::cout << "Failed GLFW initialization" << std::endl;
		return -1;
	}

	window = glfwCreateWindow(width, height, "OpenGL-cube", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		std::cout << "Failed creating window" << std::endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	// initialize glew
	if (glewInit() != GLEW_OK) 
	{
		std::cout << "Failed Glew initialization" << std::endl;
		return -1;
	}


	// Create the cube
	Cube cube1;

	// Create shaders
	Shader shaderProgram = Shader("res/shaders/vertexShader.vert", "res/shaders/fragmentShader.frag");
	glUseProgram(shaderProgram.id);

	// Create uniform
	GLint timeUniformId = glGetUniformLocation(shaderProgram.id, "time");
	GLint coefficientsUniformId = glGetUniformLocation(shaderProgram.id, "coefficients");

	// Randomize the coefficients 
	glm::vec3 coeffs = glm::vec3(randomFloat(), randomFloat(), randomFloat());

	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT);

		
		// Set the uniform value
		glUniform1f(timeUniformId, glfwGetTime());
		glUniform3f(coefficientsUniformId, coeffs[0], coeffs[1], coeffs[2]);

		// Draw the cube
		cube1.draw();
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}