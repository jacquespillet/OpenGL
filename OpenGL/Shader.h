#ifndef SHADER_H
#define SHADER_H

#include <glad\glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
class Shader
{
public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		string vertexCode, fragmentCode;
		ifstream vShaderFile, fShaderFile;

		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit); fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			vShaderFile.open(vertexPath); fShaderFile.open(fragmentPath);
			
			stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf(); fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close(); fShaderFile.close();

			vertexCode = vShaderStream.str(); fragmentCode = fShaderStream.str();
		} catch(ifstream::failure e) {
			cout << "failed" << endl;
		}

		const char* vShaderCode = vertexCode.c_str(); const char* fShaderCode = fragmentCode.c_str();
		unsigned int vertex, fragment;
		int success;
		char infolog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infolog);
			std::cout << infolog << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infolog);
			std::cout << infolog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex); glAttachShader(ID, fragment);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infolog);
			cout << infolog << endl;
		}

		glDeleteShader(vertex); glDeleteShader(fragment);
	}
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath) {
		string vertexCode, fragmentCode, geometryCode;
		ifstream vShaderFile, fShaderFile, gShaderFile;

		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit); fShaderFile.exceptions(ifstream::failbit | ifstream::badbit); gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		try {
			vShaderFile.open(vertexPath); fShaderFile.open(fragmentPath); gShaderFile.open(geometryPath);

			stringstream vShaderStream, fShaderStream, gShaderStream;
			vShaderStream << vShaderFile.rdbuf(); fShaderStream << fShaderFile.rdbuf(); gShaderStream << gShaderFile.rdbuf();

			vShaderFile.close(); fShaderFile.close(); gShaderFile.close();

			vertexCode = vShaderStream.str(); fragmentCode = fShaderStream.str(); geometryCode = gShaderStream.str();
		}
		catch (ifstream::failure e) {
			cout << "failed" << endl;
		}

		const char* vShaderCode = vertexCode.c_str(); const char* fShaderCode = fragmentCode.c_str(); const char* gShaderCode = geometryCode.c_str();
		unsigned int vertex, fragment, geometry;
		int success;
		char infolog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infolog);
			std::cout << infolog << std::endl;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infolog);
			std::cout << infolog << std::endl;
		}

		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(geometry, 512, NULL, infolog);
			std::cout << infolog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex); glAttachShader(ID, fragment); glAttachShader(ID, geometry);
		glLinkProgram(ID);
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infolog);
			cout << infolog << endl;
		}

		glDeleteShader(vertex); glDeleteShader(fragment); glDeleteShader(geometry);
	}
	void use() {
		glUseProgram(ID);
	}
	void setBool(const std::string &name, bool value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	void setInt(const std::string &name, int value) {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setFloat(const std::string &name, float value) {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	void setMat4(const std::string &name, glm::mat4 value) {
		unsigned int viewLoc = glGetUniformLocation(ID, name.c_str());
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(value));
	}
	void setVec3(const std::string &name, glm::vec3 value) {
		unsigned int viewLoc = glGetUniformLocation(ID, name.c_str());
		glUniform3f(viewLoc, value[0], value[1], value[2]);
	}
	~Shader() {}
};

#endif
