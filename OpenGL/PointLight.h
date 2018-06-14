#pragma once
#include "Light.h"
class PointLight :
	public Light
{	
public:
	glm::vec3 position;
	double constant, linear, quadratic;
	PointLight(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _position, float _constant, float _linear, float _quadratic) : 
		Light(_ambient, _diffuse, _specular),
		position(_position),
		constant(_constant), linear(_linear), quadratic(_quadratic)
	{}
	~PointLight() {}
	void attachToShader(Shader shader, const std::string varName) {
		shader.use();
		shader.setVec3(varName + ".position", position);
		shader.setVec3(varName + ".ambient", ambient);
		shader.setVec3(varName + ".diffuse", diffuse);
		shader.setVec3(varName + ".specular", specular);
		shader.setFloat(varName + ".constant", constant);
		shader.setFloat(varName + ".linear", linear);
		shader.setFloat(varName + ".quadratic", quadratic);
	}
};

