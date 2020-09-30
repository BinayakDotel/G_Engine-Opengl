#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class OrthoCamera {
private:
	glm::mat4 m_ModelViewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;

	glm::vec3 m_Position;
	float m_Rotation = 0.0f;
	glm::vec3 m_Scale;

public:
	OrthoCamera(float left, float right, float bottom, float top, float far, float near);

	void setPosition(glm::vec3 position) { m_Position = position; updateTransform(); }
	const glm::vec3& getPosition() const { return m_Position; }

	void setRotation(float rotation) { m_Rotation = rotation; updateTransform();}
	float getRotation() const { return m_Rotation; }

	void setScale(glm::vec3 scale) { m_Scale = scale; updateTransform(); }
	const glm::vec3& getScale() const { return m_Scale; }

	const glm::mat4 getModelViewMatrix() const { return m_ModelViewMatrix; }

	void updateTransform();
};