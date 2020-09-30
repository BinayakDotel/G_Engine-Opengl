#include "glm.hpp"

class PrespCamera {
private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ModelViewMatrix;
	glm::mat4 m_ViewMatrix;

	glm::vec3 c_Position={ 0.0f, 0.0f, 0.0f };
	glm::vec3 c_Forward={ 0.0f, 0.0f, -1.0f };
	glm::vec3 c_up ={ 0.0f, 1.0f, 0.0f };
	
public:
	PrespCamera(glm::vec3 pos, float fov, float aspect, float znear, float zfar);
	
	void setPosition(glm::vec3 position) { c_Position = position; updateTransform(); }
	const glm::vec3& getPosition() const { return c_Position; }

	void moveForward(glm::vec3 forward) { c_Forward = forward; updateTransform(); }
	const glm::vec3& getForward() const { return c_Forward; }

	void moveUp(glm::vec3 up) { up = up; updateTransform(); }
	const glm::vec3& getUp() const { return c_up; }

	const glm::mat4 getModelViewMatrix() const;

	void updateTransform();
};