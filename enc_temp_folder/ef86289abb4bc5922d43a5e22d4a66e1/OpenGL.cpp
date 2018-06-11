// ConsoleApplication2.cpp : définit le point d'entrée pour l'application console.
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
#include "variables.h"

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
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		if (texRatio <= 1.0) {
			texRatio += 0.01f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (texRatio >= 0.0) {
			texRatio -= 0.01f;
		}
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

	//First texture
	unsigned char *data = stbi_load("images/rust.jpg", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			cout << "failed" << endl;
		}
		stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);


	//Second texture
	data = stbi_load("images/smily.jpg", &width, &height, &nrChannels, 0);
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			cout << "failed" << endl;
		}
		stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader shader("shaders/Basic.vert", "shaders/Basic.frag");
	shader.use();
	shader.setInt("ourTexture", 0);
	shader.setInt("ourTexture2", 1);

	while (!glfwWindowShouldClose(window)) {
		//Input processing
		inputFunc(window);

		//DeltaTime processing
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Rendering process
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(VAO);
			
			//Bind textures
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);
			
			shader.use();
			shader.setFloat("texRatio", texRatio);
			
			//Send matrix as uniform to vert shader
			shader.setMat4("view", camera.getViewMatrix());
			shader.setMat4("projection", glm::perspective(glm::radians(fovy), (float)800 / 600, 0.1f, 100.0f));
			for (unsigned int i = 0; i < 10 ; ++i) {
				glm::mat4 model(1.0);
				model = glm::translate(model, cubePositions[i]);
				model = glm::rotate(model, (float)glfwGetTime() *glm::radians(-50.0f), glm::vec3(0.5f, 1.0f, 0.5f));
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

