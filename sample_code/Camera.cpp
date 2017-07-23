#include "Camera.h"

Camera::Camera(){
	m_cameraPos   = glm::vec3(0.0f, 0.0f,  -3.0f);
	m_cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
	m_cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
	m_view = glm::lookAt(m_cameraPos, m_cameraPos+m_cameraFront, m_cameraUp);
	m_cameraSpeed = 3.1f;
}
glm::mat4 Camera::getView(){
	m_view = glm::lookAt(m_cameraPos, m_cameraPos+m_cameraFront, m_cameraUp);
	return m_view;
}
void Camera::move(CameraDir direction, float deltaTime){
	float speed = m_cameraSpeed*deltaTime;
	if(direction == CameraDir::FORWARD)
		m_cameraPos+= speed*m_cameraFront;
	if(direction == CameraDir::BACKWARD)
		m_cameraPos -= speed*m_cameraFront;
	if(direction == CameraDir::LEFT)
		m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp))*speed;
	if(direction == CameraDir::RIGHT)
		m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp))*speed;
}
void Camera::setCameraDir(glm::vec3 newDir){
	m_cameraFront = newDir;
}