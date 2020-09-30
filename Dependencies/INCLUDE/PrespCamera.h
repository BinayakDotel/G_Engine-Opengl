#include "glm.hpp"
#include <iostream>

class PrespCamera {
private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ModelViewMatrix;
	glm::mat4 m_ViewMatrix;

	glm::vec3 c_Position;
	glm::vec3 c_Forward;
	glm::vec3 c_Up;
	
public:
	PrespCamera(float fov, float aspect, float znear, float zfar);
	
	void setPosition(glm::vec3 position) { c_Position = position; updateTransform(); }
	const glm::vec3& getPosition() const { return c_Position; }

	void moveForward(glm::vec3 forward) { c_Forward = forward; updateTransform(); }
	const glm::vec3& getForward() const { return c_Forward; }

	void moveUp(glm::vec3 up) { c_Up = up; updateTransform(); }
	const glm::vec3& getUp() const { return c_Up; }

	void prt() { 
		glm::vec3 a={ 0.0f, 1.0f, 0.0f };
		glm::vec3 b={ 1.0f, 0.0f, 0.0f };
		float angle= glm::dot(a, b);
		float cosine= cos(glm::dot(a, b));
		glm::vec3 cross= glm::cross(a, b);

		std::cout << "angle: " << angle << std::endl;
		std::cout << "cosine: " << cosine << std::endl;
		std::cout << "cross: " << cross.x << ", " << cross.y << ", " << cross.z << std::endl;
	}

	const glm::mat4 getModelViewMatrix() const;

	void updateTransform();
};