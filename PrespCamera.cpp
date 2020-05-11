#include <PrespCamera.h>
#include "gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

PrespCamera::PrespCamera(glm::vec3 pos, float fov, float aspect, float znear, float zfar)
	:c_Position(pos),
	m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, znear, zfar)),
	m_ViewMatrix(glm::lookAt(c_Position, c_Position + c_Forward, c_up))
{
	m_ModelViewMatrix= m_ProjectionMatrix * m_ViewMatrix;
}

const glm::mat4 PrespCamera :: getModelViewMatrix() const { return m_ModelViewMatrix; }

void PrespCamera::updateTransform() { 
	m_ViewMatrix= glm::lookAt(c_Position, c_Position + c_Forward, c_up);
	m_ModelViewMatrix= m_ProjectionMatrix * m_ViewMatrix;
}