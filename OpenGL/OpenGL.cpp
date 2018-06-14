// ConsoleApplication2.cpp�: d�finit le point d'entr�e pour l'application console.
//
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Shader.h"
#include "libs/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "variables.h"
#include "utils.h"

using namespace std;

void resizeFunc(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouseFunc(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos; lastY = ypos;
		firstMouse = false;
	}
	float xOffset = xpos - lastX; float yOffset = lastY - ypos;
	lastX = xpos; lastY = ypos;
	camera.processMouse(xOffset, yOffset);
}

void inputFunc(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (fovy <= 90.0) {
			fovy += 1.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (fovy >= 0.0) {
			fovy -= 1.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		lightTurning = !lightTurning;
	}
}

void init() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 600, "Jacques", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed" << std::endl;
		glfwTerminate();
		exit;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		exit;
	}

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(window, resizeFunc);
	glfwSetCursorPosCallback(window, mouseFunc);
	
	stbi_set_flip_vertically_on_load(true);

}

int main()
{
	init();

	glGenVertexArrays(1, &VAO); 
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(lightVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
			glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	unsigned int diffuseMap = loadTexture("images/container2.png");
	unsigned int specularMap = loadTexture("images/container2_specular.png");

	Shader lightShader("shaders/Light.vert", "shaders/Light.frag");

	Shader shader("shaders/Reflect.vert", "shaders/Reflect.frag");
	shader.use();
	shader.setVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	shader.setVec3("viewPos", camera.position);

	shader.setInt("material.diffuseMap", 0);
	shader.setInt("material.specularMap", 1);
	shader.setFloat("material.shininess", 64.0);
	

	DirectionalLight light = DirectionalLight(glm::vec3(0.3), glm::vec3(0.5), glm::vec3(1.0f), glm::vec3(-1.0, 0.0, -1.0));
	light.attachToShader(shader, "light");

	PointLight pointLight = PointLight(glm::vec3(0.3, 0.5, 0.8), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.6, 0.8, 0.76), pointLightPositions[0], 1.0, 0.35, 0.44);
	pointLight.attachToShader(shader, "pointLights[0]");
	PointLight pointLight1 = PointLight(glm::vec3(0.3, 0.5, 0.8), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.6, 0.8, 0.76), pointLightPositions[1], 1.0, 0.35, 0.44);
	pointLight1.attachToShader(shader, "pointLights[1]");
	PointLight pointLight2 = PointLight(glm::vec3(0.3, 0.5, 0.8), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.6, 0.8, 0.76), pointLightPositions[2], 1.0, 0.35, 0.44);
	pointLight2.attachToShader(shader, "pointLights[2]");
	PointLight pointLight3 = PointLight(glm::vec3(0.3, 0.5, 0.8), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.6, 0.8, 0.76), pointLightPositions[3], 1.0, 0.35, 0.44);
	pointLight3.attachToShader(shader, "pointLights[3]");


	while (!glfwWindowShouldClose(window)) {
		//Input processing
		inputFunc(window);

		//DeltaTime processing
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Rendering process
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(fovy), (float)800 / 600, 0.1f, 100.0f);
		glm::mat4 view = camera.getViewMatrix();

		glBindVertexArray(lightVAO);			
			lightShader.use();
			lightShader.setMat4("view", view);
			lightShader.setMat4("projection", projection);

			glm::mat4 model(1.0);
			for (int i = 0; i < 4; i++) {
				model = glm::mat4(1.0);
				model = glm::translate(model, pointLightPositions[i]);
				model = glm::scale(model, glm::vec3(0.2));
				lightShader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

		glBindVertexArray(0);


		glBindVertexArray(VAO);
			shader.use();
			//Geometry
			shader.setMat4("view", view);
			shader.setMat4("projection", projection);

			//Texture 
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseMap);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, specularMap);

			//Lighting 
			shader.setVec3("viewPos", camera.position);
			

			for (unsigned int i = 0; i < 10; i++)
			{
				model = glm::mat4(1.0);
				model = glm::translate(model, cubePositions[i]);
				float angle = 20.0f * i;
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
				shader.setMat4("model", model);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

