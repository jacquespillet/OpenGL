#pragma once
GLFWwindow* window;

float fovy = 45.0; //Zoom

float deltaTime = 0.0f; //Time between each frame
float lastFrame = 0.0f;

float lastX = 400, lastY = 300; //For mouse movements
bool firstMouse = true;
bool lightTurning = false;
float shininess = 16.0;
bool blinn = true;
bool blinnKeyPressed = false;
bool shadowsKeyPressed = false;
bool shadows = true;

Camera camera(glm::vec3(1.0f, 1.0f, 5.0f));
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;


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

glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.5f,  0.0f),
	glm::vec3(2.0f,  0.5f, -15.0f),
	glm::vec3(-2.5f, 0.5f, -2.5f),
	glm::vec3(3.8f, 0.5f, -12.3f),
	glm::vec3(2.4f, 0.5f, -3.5f),
	glm::vec3(-3.7f,  0.5f, -7.5f),
	glm::vec3(1.3f, 0.5f, -2.5f),
	glm::vec3(1.5f,  0.5f, -2.5f),
	glm::vec3(3.0f,  0.5f, -1.5f),
	glm::vec3(-1.3f,  0.5f, -1.5f)
};

float floorVertices[] = {
	// positions          // normals            // texture coords
	-10.0, -0.0f, -10.0,   0.0f, 1.0f, 0.0f,		0.0f, 2.0F,
	10.0, -0.0f, -10.0,    0.0f, 1.0f, 0.0f,		2.0F, 2.0F,
	10.0, -0.0f, 10.0,     0.0f, 1.0f, 0.0f,		2.0F, 0.0f,
	10.0, -0.0f, 10.0,     0.0f, 1.0f, 0.0f,		2.0F, 0.0f,
	-10.0, -0.0f, 10.0,    0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
	-10.0, -0.0f, -10.0,   0.0f, 1.0f, 0.0f,		0.0f, 2.0F
};



glm::vec3 pointLightPositions[] = {
	glm::vec3(-8.0f,  1.0f,  0.0f),
	glm::vec3(-4.0f, 1.0f, 0.0f),
	glm::vec3(0.0f,  1.0f, 0.0f),
	glm::vec3(4.0f,  1.0f, 0.0f)
};