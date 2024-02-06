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

float randomFloat() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 5.0);



    return dis(gen);
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

	glUniform3f(timeUniformId, 0.5f, 0.2f, 0.9f);

	float time = 0.0f;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		time += 0.1;
		glClear(GL_COLOR_BUFFER_BIT);

		
		// Set the uniform value
		glUniform1f(timeUniformId, glfwGetTime());
		glUniform3f(timeUniformId, randomFloat(), randomFloat(), randomFloat());

		// Draw the cube
		cube1.draw();
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}