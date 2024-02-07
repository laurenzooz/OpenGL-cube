#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
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
	TexturedCube cube;
	
	// Create texture and bind it
	Texture tex = Texture("res/textures/tex.png");
	tex.bind();

	// Create shaders and activate the shaderprogram
	Shader shaderProgram = Shader("res/shaders/vertexShader.vert", "res/shaders/fragmentShader.frag");
	glUseProgram(shaderProgram.id);

	// Create uniforms
	GLint timeUid = glGetUniformLocation(shaderProgram.id, "time");

	// Model, view and projection matrices
	GLint cubeModelUid = glGetUniformLocation(shaderProgram.id, "model");
	GLint cubeViewUid = glGetUniformLocation(shaderProgram.id, "view");
	GLint cubeProjUid = glGetUniformLocation(shaderProgram.id, "projection");

	// Texture
	GLint cubeTextureUid = glGetUniformLocation(shaderProgram.id, "texImg");
	GLint cubeUseTexUid = glGetUniformLocation(shaderProgram.id, "useTexture");

	// Color
	GLint cubeColorUid = glGetUniformLocation(shaderProgram.id, "color");
	GLint cubeUseVariationUid = glGetUniformLocation(shaderProgram.id, "colorVariation"); // wheter to use color variation or not



	// Get the uniform values

	// initialize matrices with ones.
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	

	// Translations and rotations
	float distance = 2.0f;
	// save the old one to calculate the difference to new one to know how much needs to be moved
	float prevDistance = distance; 
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -distance)); 

	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f); // keep track of the rotations around different axes
	glm::vec3 prevRotation = rotation;
	
	
	// build the perspective projection matrix
	projection = glm::perspective(45.0f, (float)width  / (float)height, 0.1f, 100.0f);

	// When not using a texture, set this to false (and the cube will have normal color instead
	bool useTexture = true; 
	bool useVariation = false;  // uniform color or the automatic variation over time
	glm::vec4 cubeColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // imgui requires vec4


	// Set the uniforms initial state

	glUniformMatrix4fv(cubeViewUid, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(cubeProjUid, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform1f(cubeTextureUid, tex.id);
	glUniform1i(cubeUseTexUid, useTexture);

	glUniform3f(cubeColorUid, cubeColor[0], cubeColor[1], cubeColor[2]);
	glUniform1i(cubeUseVariationUid, useVariation);


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
		
		// cube
		glUseProgram(shaderProgram.id);
		
		// Set the uniform values that change over time
		glUniform1f(timeUid, glfwGetTime());

		glUniformMatrix4fv(cubeModelUid, 1, GL_FALSE, glm::value_ptr(model));

		// Draw the cube	
		cube.draw();


		// Imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        ImGui::Begin("OpenGL-cube");

        ImGui::Text("More settings to be added.");
            
        if (ImGui::SliderFloat("Distance", &distance, 1.0f, 5.0f))
		{
			// Calculate like this so the slider moves the cube towards user, not towards the front of the cube
			glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, prevDistance - distance));
			model = translate * model; 
		}
			
		
		if (ImGui::SliderFloat("Rotate around X", &rotation[0], -180.0f, 180.0f))
			model = glm::rotate(model, glm::radians(prevRotation[0] - rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		
		if (ImGui::SliderFloat("Rotate around Y", &rotation[1], -180.0f, 180.0f))
			model = glm::rotate(model, glm::radians(prevRotation[1] - rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		
		if (ImGui::SliderFloat("Rotate around Z", &rotation[2], -180.0f, 180.0f))
			model = glm::rotate(model, glm::radians(prevRotation[2] - rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f));

		// Toggle texture
		if (ImGui::RadioButton("Texture", useTexture))
		{
			if (useTexture) useTexture = false; else useTexture = true;
			glUniform1i(cubeUseTexUid, useTexture); // only set the uniform if the button status changes
		}
		
		// Toggle color variation
		if (!useTexture && ImGui::RadioButton("Color variation", useVariation))
		{
			if (useVariation) useVariation = false; else useVariation = true;
			glUniform1i(cubeUseVariationUid, useVariation);
		}

		// Select custom color when not using variation or texture
		if (!useTexture && !useVariation && ImGui::ColorEdit3("Select color", glm::value_ptr(cubeColor)))	
			glUniform3f(cubeColorUid, cubeColor[0], cubeColor[1], cubeColor[2]);
		
			


		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		prevDistance = distance;
		prevRotation = rotation;




		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}