#pragma once
#include <string>
#include "glm.hpp"

class Shader {
private:
	unsigned int m_renderer_id;
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();

	void bindShader() const;
	void unbindShader() const;
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string& source);

	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniformMat4f(const std::string& name, const glm::mat4 matrix);
	void setUniform1iv(const std::string& name);
	int getUniformLocation(const std::string& name);
};
