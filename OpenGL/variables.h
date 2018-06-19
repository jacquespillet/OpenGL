#pragma once
#include <vector>

GLFWwindow* window;

float fovy = 45.0; //Zoom

float deltaTime = 0.0f; //Time between each frame
float lastFrame = 0.0f;

float lastX = 400, lastY = 300; //For mouse movements
bool firstMouse = true;
bool lightTurning = false;
float lightDist = 2.0;

Camera camera(glm::vec3(1.0f, 1.0f, 5.0f));

std::vector<std::string> faces;

unsigned int VAO, VBO;
unsigned int lightVAO;
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

float floorVertices[] = {
	// positions          // normals            // texture coords
	-10.0, -1.0f, -10.0,   0.0f, 1.0f, 0.0f,		0.0f, 5.0f,
	10.0, -1.0f, -10.0,    0.0f, 1.0f, 0.0f,		5.0f, 5.0f,
	10.0, -1.0f, 10.0,     0.0f, 1.0f, 0.0f,		5.0f, 0.0f,
	10.0, -1.0f, 10.0,     0.0f, 1.0f, 0.0f,		5.0f, 0.0f,
	-10.0, -1.0f, 10.0,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	-10.0, -1.0f, -10.0,   0.0f, 1.0f, 0.0f,		0.0f, 5.0f
};
unsigned int floorVAO, floorVBO;

float grassVertices[] = {
	-0.5f, 0.0f,  0.0f,   0.0f,  0.0f,
	0.5f,  0.0f,  0.0f,    1.0f,  0.0f,
	0.5f,  1.0f,  0.0f,    1.0f,  1.0f,
	0.5f,  1.0f,  0.0f,    1.0f,  1.0f,
	-0.5f, 1.0f,  0.0f,   0.0f,  1.0f,
	-0.5f, 0.0f,  0.0f,   0.0f,  0.0f,
};
glm::vec3 grassLocations[] = {
	glm::vec3(-1.5f,  -1.0f, -0.48f),
	glm::vec3(1.5f,  -1.0f,  0.51f),
	glm::vec3(0.0f,  -1.0f,  0.7f),
	glm::vec3(-0.3f,  -1.0f, -2.3f),
	glm::vec3(0.5f,  -1.0f, -0.6f)
};

glm::vec3 windowLocations[] = {
	glm::vec3(-2.5f, -1.0f, -2.48f),
	glm::vec3(-1.5f, -1.0f, 1.51f),
	glm::vec3(0.5f, -1.0f, -0.7f),
	glm::vec3(-1.3f, -1.0f, 2.3f),
	glm::vec3(1.5f, -1.0f, -2.6f)
};
unsigned int grassVAO, grassVBO;




glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  -1.0f,  0.0f),
	glm::vec3(2.0f,  -1.0f, -15.0f),
	glm::vec3(-2.5f, -1.0f, -2.5f),
	glm::vec3(3.8f, -1.0f, -12.3f),
	glm::vec3(2.4f, -1.0f, -3.5f),
	glm::vec3(-3.7f,  -1.0f, -7.5f),
	glm::vec3(1.3f, -1.0f, -2.5f),
	glm::vec3(1.5f,  -1.0f, -2.5f),
	glm::vec3(3.0f,  -1.0f, -1.5f),
	glm::vec3(-1.3f,  -1.0f, -1.5f)
};

//Lights
glm::vec3 lightPos(1.0f, 0.0f, 0.0f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
float ambientStrength = 0.2;
float specularStrength= 0.7;
glm::vec3 ambient = ambientStrength * lightColor;

glm::vec3 pointLightPositions[] = {
	glm::vec3(0.7f,  -1.0f,  2.0f),
	glm::vec3(2.3f, -1.0f, -1.0f),
	glm::vec3(-2.0f,  -1.0f, -2.0f),
	glm::vec3(0.0f,  -1.0f, -1.5f)
};


unsigned int skyBoxVAO, skyBoxVBO;

float skyBoxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};