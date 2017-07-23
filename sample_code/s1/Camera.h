#ifndef CAMERA_H
#define CAMERA_H
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
enum CameraDir{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};
class Camera{
private:
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_cameraUp;
	glm::mat4 m_view;
	float m_cameraSpeed;
public:
	Camera();
	glm::mat4 getView();
	void move(CameraDir direction, float deltaTime);
	void setCameraDir(glm::vec3 newDir);

};
#endif