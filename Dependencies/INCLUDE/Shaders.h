#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

class Shaders {
private:
	unsigned int pid;
public:
	Shaders();
	~Shaders();
	void bindShader() const;
	void unbindShader() const;
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string& source);
	void setUniformMat4f(const std::string& name, const glm::mat4 matrix);
	void setUniform1iv(const std::string& name);
	int getUniformLocation(const std::string& name);
};

