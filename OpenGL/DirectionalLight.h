#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	glm::vec3 position;
	DirectionalLight(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _position) : 
		Light(_ambient, _diffuse, _specular), 
		position(_position) {}

	~DirectionalLight() {}
	virtual void attachToShader(Shader shader, const std::string varName) {
		shader.use();
		shader.setVec3(varName + ".ambient", ambient);
		shader.setVec3(varName + ".diffuse", diffuse);
		shader.setVec3(varName + ".specular", specular);
		shader.setVec3(varName + ".direction", specular);
	}
};

