#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Cube.h"
#include "Shader.h"
#include "Texture.h"

const unsigned int width = 800;
const unsigned int height = 600;

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
	TexturedCube cube1;

	// Create texture and bind it
	Texture tex = Texture("res/textures/tex.png");
	tex.bind();

	// Create shaders and activate the shaderprogram
	Shader shaderProgram = Shader("res/shaders/vertexShader.vert", "res/shaders/fragmentShader.frag");
	glUseProgram(shaderProgram.id);

	// Create uniforms
	GLint timeUniformId = glGetUniformLocation(shaderProgram.id, "time");
	GLint coefficientsUniformId = glGetUniformLocation(shaderProgram.id, "coefficients");

	// Model, view and projection matrices
	GLint modelMatUniformId = glGetUniformLocation(shaderProgram.id, "model");
	GLint viewMatUniformId = glGetUniformLocation(shaderProgram.id, "view");
	GLint projMatUniformId = glGetUniformLocation(shaderProgram.id, "projection");

	// Texture
	GLint textureUniformId = glGetUniformLocation(shaderProgram.id, "texImg");
	GLint useTextureUniformId = glGetUniformLocation(shaderProgram.id, "useTexture");



	// Get the uniform values

	// Randomize the coefficients 
	glm::vec3 coeffs = glm::vec3(randomFloat(), randomFloat(), randomFloat());

	// initialize matrices with ones.
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	
	// move model up and further from camera
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f)); 
	
	// build the perspective projection matrix
	projection = glm::perspective(45.0f, (float)width  / (float)height, 0.1f, 100.0f);

	// When not using a texture, set this to false (and the cube will have the chanding color instead)
	bool useTexture = true; 




	// Set the uniforms that aren't constantly changed
	glUniform3f(coefficientsUniformId, coeffs[0], coeffs[1], coeffs[2]);

	glUniformMatrix4fv(viewMatUniformId, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projMatUniformId, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(textureUniformId, tex.id);
	glUniform1i(useTextureUniformId, useTexture);

	

	glEnable(GL_DEPTH_TEST);
	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		// Make the cube spin
		model = glm::rotate(model, 0.01f, glm::vec3(0.2f, 0.8f, 0.0f));


		
		// Set the uniform values that change over time
		glUniform1f(timeUniformId, glfwGetTime());

		glUniformMatrix4fv(modelMatUniformId, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the cube
		cube1.draw();
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}