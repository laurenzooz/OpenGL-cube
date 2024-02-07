#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

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
	

	// zoom
	float distance = 2.0f;
	float oldDistance = distance; // to keep track of the amount needed to be zoomed
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -distance)); 
	float rotateSpeed = 0.01f;
	
	
	// build the perspective projection matrix
	projection = glm::perspective(45.0f, (float)width  / (float)height, 0.1f, 100.0f);

	// When not using a texture, set this to false (and the cube will have the chanding color instead)
	bool useTexture = true; 




	// Set the uniforms initial state
	glUniform3f(coefficientsUniformId, coeffs[0], coeffs[1], coeffs[2]);

	glUniformMatrix4fv(viewMatUniformId, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projMatUniformId, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(textureUniformId, tex.id);
	glUniform1i(useTextureUniformId, useTexture);
	


	// Initialize imgui 
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	glEnable(GL_DEPTH_TEST);
	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		// Make the cube spin
		model = glm::rotate(model, rotateSpeed, glm::vec3(0.2f, 0.8f, 0.0f));

		

		
		// Set the uniform values that change over time
		glUniform1f(timeUniformId, glfwGetTime());

		glUniformMatrix4fv(modelMatUniformId, 1, GL_FALSE, glm::value_ptr(model));

		// Draw the cube
		cube1.draw();
		

		// Imgui

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        ImGui::Begin("OpenGL-cube");

        ImGui::Text("More settings to be added.");
            
        ImGui::SliderFloat("Rotate speed", &rotateSpeed, 0.0f, 0.1f);
        if (ImGui::SliderFloat("Distance", &distance, 1.0f, 5.0f));
		{
			glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, oldDistance - distance));
			model = translation * model; // calculate the translation matrix needed and multiply with the current, rotated model matrix
		}

		if (ImGui::RadioButton("Texture", useTexture))
		{
			if (useTexture) useTexture = false; else useTexture = true;
			glUniform1i(useTextureUniformId, useTexture); // only set the uniform if the button status changes
		}
			


		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		oldDistance = distance;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}