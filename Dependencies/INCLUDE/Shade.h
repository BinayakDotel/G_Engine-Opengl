#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Error.h>
#include <glm.hpp>

class Shade {
public:
	GLuint pid;
	Shade();
	~Shade();
	void setUniformMat4f(const std::string& name,
		const glm::mat4 matrix);
	void setUniform1iv(const std::string& name);
	int getUniformLocation(const std::string& name);
};
