#include <PrespCamera.h>
#include "gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

PrespCamera::PrespCamera(float fov, float aspect, float znear, float zfar)
	:c_Position(glm::vec3(0.0f, 0.0f, 3.0f)),
	c_Forward(glm::vec3(0.0f, 0.0f, -1.0f)),
	c_Up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, znear, zfar))
{
	m_ViewMatrix= glm::lookAt(c_Position, c_Position + c_Forward, c_Up);
	m_ModelViewMatrix= m_ProjectionMatrix * m_ViewMatrix; 
}

const glm::mat4 PrespCamera :: getModelViewMatrix() const { return m_ModelViewMatrix; }

void PrespCamera::updateTransform() { 
	m_ViewMatrix= glm::lookAt(c_Position, c_Position + c_Forward, c_Up);
	//m_Model= glm::
	m_ModelViewMatrix= m_ProjectionMatrix * m_ViewMatrix;
}