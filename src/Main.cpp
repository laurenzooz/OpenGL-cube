#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL // to use vector rotation
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"

#include "Cube.h"
#include "Plane.h"
#include "Shader.h"
#include "Texture.h"

const unsigned int width = 800;
const unsigned int height = 600;



// Camera movement
glm::mat4 moveCamera(GLFWwindow* window, glm::vec3 &eyePos, glm::vec3 &eyeDir)
{
	
	float speed = 0.05f;
	glm::vec3 direction = glm::normalize(eyeDir);

	// Key inputs to move
	if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) eyePos += direction * speed; // forward
	if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) eyePos -= direction * speed; // back

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
	{
		eyePos += glm::vec3(0.0f, 1.0f, 0.0f) * speed; // Up
		eyeDir += glm::vec3(0.0f, 1.0f, 0.0f) * speed; // Move the "aiming point" as well, so the camera moves straight up

	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
	{
		eyePos += glm::vec3(-1.0f, 0.0f, 0.0f) * speed; // Left
		eyeDir += glm::vec3(-1.0f, 0.0f, 0.0f) * speed; // Left
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) 
	{
		eyePos += glm::vec3(0.0f, -1.0f, 0.0f) * speed; // Down
		eyeDir += glm::vec3(0.0f, -1.0f, 0.0f) * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) 
	{
		eyePos += glm::vec3(1.0f, 0.0f, 0.0f) * speed; // Right
		eyeDir += glm::vec3(1.0f, 0.0f, 0.0f) * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) eyeDir += glm::vec3(0.0f, 1.0f, 0.0f) * speed;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) eyeDir += glm::vec3(0.0f, -1.0f, 0.0f) * speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) eyeDir += glm::vec3(-1.0f, 0.0f, 0.0f) * speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) eyeDir += glm::vec3(1.0f, 0.0f, 0.0f) * speed;

	return glm::lookAt(eyePos, eyeDir, glm::vec3(0.0f, 1.0f, 0.0f));
}


int main()
{
	srand(time(0));
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window handle
	GLFWwindow* window;

	// initialize glfw
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

	// The light source color and position
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-0.5f, 0.5f, 0.0f);
	float ambient = 0.2f; // ambient light intesity


	// Create the cube
	TexturedCube cube;
	
	// Create texture and bind it
	Texture tex = Texture("res/textures/tex.png");
	tex.bind();

	// Create shaders and activate the shaderprogram
	Shader shaderProgram = Shader("res/shaders/objectShader.vert", "res/shaders/objectShader.frag");
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

	// Light
	GLint cubeLightUid = glGetUniformLocation(shaderProgram.id, "lightColor");
	GLint cubeLightPosUid = glGetUniformLocation(shaderProgram.id, "lightPos");
	GLint cubeAmbientUid = glGetUniformLocation(shaderProgram.id, "ambient");
	GLint cubeEyePosUid = glGetUniformLocation(shaderProgram.id, "eyePos");



	// Get the uniform values

	// initialize matrices with ones.
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	

	// Set the initial position and projections
	glm::vec2 cubePos = glm::vec2(0.0f, 0.0f); // x, z on the flat plane
	glm::vec2 prevCubePos = cubePos; // save to know the translation amount when moving from the menu
	model = glm::translate(model, glm::vec3(cubePos[0], 0.0f, cubePos[1])); 

	float rotation = 0.0f; // angle around y axis
	float prevRotation = 0.0f;


	// View matrix
	glm::vec3 eyePos = glm::vec3(2.0f, 2.0f, 2.0f); 
	glm::vec3 eyeDir = glm::vec3(0.0f) - eyePos; 

	view = glm::lookAt(eyePos, eyeDir, glm::vec3(0.0f, 1.0f, 0.0f));

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

	glUniform3f(cubeLightUid, lightColor[0], lightColor[1], lightColor[2]);
	glUniform3f(cubeLightPosUid, lightPos[0], lightPos[1], lightPos[2]);
	glUniform3f(cubeEyePosUid, eyePos[0], eyePos[1], eyePos[2]);
	glUniform1f(cubeAmbientUid, ambient);


	



	// Create floor
	Plane floor(2.0f);
	// Create shaders and activate the shaderprogram
	Shader floorShader = Shader("res/shaders/groundShader.vert", "res/shaders/groundShader.frag");
	glUseProgram(floorShader.id);

	// Model, view and projection matrix uniforms
	GLint floorModelUid = glGetUniformLocation(floorShader.id, "model");
	GLint floorViewUid = glGetUniformLocation(floorShader.id, "view");
	GLint floorProjUid = glGetUniformLocation(floorShader.id, "projection");

	// Light
	GLint floorLightUid = glGetUniformLocation(floorShader.id, "lightColor");
	GLint floorLightPosUid = glGetUniformLocation(floorShader.id, "lightPos");
	GLint floorAmbientUid = glGetUniformLocation(floorShader.id, "ambient");
	GLint floorEyePostUid = glGetUniformLocation(floorShader.id, "eyePos");

	// Move down by the cube size so the cube lies flat on the ground
	glm::mat4 floorModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.25f, 0.0f)); 

	// Set the uniform values, use same view and projection matrices
	glUniformMatrix4fv(floorModelUid, 1, GL_FALSE, glm::value_ptr(floorModel)); 
	glUniformMatrix4fv(floorViewUid, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(floorProjUid, 1, GL_FALSE, glm::value_ptr(projection));

	glUniform3f(floorLightUid, lightColor[0], lightColor[1], lightColor[2]);
	glUniform3f(floorLightPosUid, lightPos[0], lightPos[1], lightPos[2]);
	glUniform1f(floorAmbientUid, ambient);
	glUniform3f(floorEyePostUid, eyePos[0], eyePos[1], eyePos[2]);




	// Create Light
	Cube light = Cube(0.1f);

	Shader lightShader = Shader("res/shaders/lightShader.vert", "res/shaders/lightShader.frag");
	glUseProgram(lightShader.id);

	// Model, view and projection matrix uniforms, and light color
	GLint lightModelUid = glGetUniformLocation(lightShader.id, "model");
	GLint lightViewUid = glGetUniformLocation(lightShader.id, "view");
	GLint lightProjUid = glGetUniformLocation(lightShader.id, "projection");

	GLint lightColorUid = glGetUniformLocation(lightShader.id, "color");

	// Move down by the cube size so the cube lies flat on the ground
	glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), glm::vec3(lightPos[0], lightPos[1], lightPos[2])); 

	// Set the uniform values, use same view and projection matrices
	glUniformMatrix4fv(lightModelUid, 1, GL_FALSE, glm::value_ptr(lightModel)); 
	glUniformMatrix4fv(lightViewUid, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(lightProjUid, 1, GL_FALSE, glm::value_ptr(projection));

	

	// Set the light color uniform
	glUniform3f(lightColorUid, lightColor[0], lightColor[1], lightColor[2]);


	

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

		// Floor
		glUseProgram(floorShader.id);
		// Uniforms
		glUniform1f(floorAmbientUid, ambient);
		glUniformMatrix4fv(floorViewUid, 1, GL_FALSE, glm::value_ptr(view));
		floor.draw();

		// Light
		glUseProgram(lightShader.id);
		glUniformMatrix4fv(lightViewUid, 1, GL_FALSE, glm::value_ptr(view));
		light.draw();
		
		// cube
		glUseProgram(shaderProgram.id);
		
		// Set the uniform values that change over time
		glUniform1f(timeUid, glfwGetTime());
		glUniform1f(cubeAmbientUid, ambient);

		glUniformMatrix4fv(cubeModelUid, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(cubeViewUid, 1, GL_FALSE, glm::value_ptr(view));


		// Draw the cube	
		cube.draw();


		// Imgui
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        ImGui::Begin("OpenGL-cube");
            
        if (ImGui::SliderFloat("X position", &cubePos[0], -1.0f, 1.0f))
		{
			// Calculate like this so the slider moves the cube towards user, not towards the front of the cube
			glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(prevCubePos[0] - cubePos[0], 0.0f, 0.0f));
			model = translate * model; 
		}

		if (ImGui::SliderFloat("Z position", &cubePos[1], -1.0f, 1.0f))
		{
			glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, prevCubePos[1] - cubePos[1]));
			model = translate * model; 
		}
	
		if (ImGui::SliderFloat("Rotate", &rotation, -180.0f, 180.0f))
			model = glm::rotate(model, glm::radians(prevRotation - rotation), glm::vec3(0.0f, 1.0f, 0.0f));
		
		ImGui::SliderFloat("Ambient light", &ambient, 0.0f, 1.0f);

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

		// Camera movement
		view = moveCamera(window, eyePos, eyeDir);
		
		prevCubePos = cubePos;
		prevRotation = rotation;
	

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}





