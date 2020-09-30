#include <OrthoCameraController.h>
#include <GLFW/glfw3.h>
#include <print.h>

/*#include "GLCore/Core/Input.h"
#include "GLCore/Core/KeyCodes.h"
*/

OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotation)
	: m_AspectRatio(aspectRatio), 
	m_ZoomLevel(1.0),
	m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation) {

	m_CameraPosition ={ 0.0f, 0.0f, 0.0f };
	m_CameraRotation = 0.0f; //In degrees, in the anti-clockwise direction
	m_CameraTranslationSpeed = 5.0f;
	m_CameraRotationSpeed = 180.0f;
}

void OrthoCameraController :: OnUpdate(TimeStep ts, GLFWwindow* window){
	this->wind= window;
	if (glfwGetKey(window, GLFW_KEY_A)) {
		print("A");
		m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}
	else if (glfwGetKey(window, GLFW_KEY_D)) {
		print("D");
		m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}

	if (glfwGetKey(window, GLFW_KEY_W)) {
		print("W");
		m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}
	else if (glfwGetKey(window, GLFW_KEY_S)) {
		print("S");
		m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
		m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
	}

	if (m_Rotation) {
		if (glfwGetKey(window, GLFW_KEY_Q))
			print("Rotate left");
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (glfwGetKey(window, GLFW_KEY_E))
			print("Rotate right");
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (m_CameraRotation > 180.0f)
			m_CameraRotation -= 360.0f;
		else if (m_CameraRotation <= -180.0f)
			m_CameraRotation += 360.0f;

		m_Camera.SetRotation(m_CameraRotation);
	}

	m_Camera.SetPosition(m_CameraPosition);

	//m_CameraTranslationSpeed = m_ZoomLevel;
}

/*void OrthoCameraController::OnEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(GLCORE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(GLCORE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}*/

/*bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
	m_ZoomLevel -= e.GetYOffset() * 0.25f;
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}*/
/*
bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e) {
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
	m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}*/
