#pragma once
#include "Shader.h"

class Light
{
public:
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light(glm::vec3 _ambient, glm::vec3 _specular, glm::vec3 _diffuse) : ambient(_ambient), diffuse(_diffuse), specular(_specular) {}
	~Light() {}
	virtual void attachToShader(Shader shader, const std::string varName) = 0;
};

