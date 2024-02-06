#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <array>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Cube.h"
#include "Shader.h"

const unsigned int width = 640;
const unsigned int height = 480;

int main()
{
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
	GLint uniformId = glGetUniformLocation(shaderProgram.id, "color");

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// Change the cube objects color
		cube1.color = glm::vec3(0.5f, 0.1f, 0.5f);

		// Set the uniform value
		glUniform3f(uniformId, cube1.color[0], cube1.color[1], cube1.color[2]);

		// Draw the cube
		cube1.draw();
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}