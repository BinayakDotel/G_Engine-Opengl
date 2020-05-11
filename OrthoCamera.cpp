#include <OrthoCamera.h>

OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float far, float near)
	:m_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), 
		m_viewMatrix(glm::mat4(1.0f))
{
	m_ModelViewMatrix = m_viewMatrix * m_projectionMatrix;
}
void OrthoCamera::updateTransform() {
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1.0f), m_Scale);
	m_viewMatrix = glm::inverse(transform);
	m_ModelViewMatrix = m_viewMatrix * m_projectionMatrix;
}