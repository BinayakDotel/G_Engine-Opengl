#pragma once

#include <OrthoCamera.h>
#include <TimeStep.h>
#include <GLFW/glfw3.h>

/*#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/MouseEvent.h"*/


class OrthoCameraController {
	private:
		//bool OnMouseScrolled(MouseScrolledEvent& e);
		//bool OnWindowResized(WindowResizeEvent& e);
		GLFWwindow* wind;

		float m_AspectRatio;
		float m_ZoomLevel;
		OrthoCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition;
		float m_CameraRotation; //In degrees, in the anti-clockwise direction
		float m_CameraTranslationSpeed, m_CameraRotationSpeed;
	public:
		OrthoCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(TimeStep ts, GLFWwindow *window);
		//void OnEvent(Event& e);

		OrthoCamera& GetCamera() { return m_Camera; }
		const OrthoCamera& GetCamera() const { return m_Camera; }

		//float GetZoomLevel() const { return m_ZoomLevel; }
		//void SetZoomLevel(float level) { m_ZoomLevel = level; }
};

