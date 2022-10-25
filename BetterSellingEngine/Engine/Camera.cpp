#include "Camera.h"

Camera* Camera::camInstance = nullptr;
Camera* Camera::GetInstance(Dimensions d) {
	if (!camInstance)
		camInstance = new Camera(d);
	return camInstance;
}
Camera* Camera::MainCamera() {
	if (!camInstance)
		camInstance = new Camera(Two);
	return camInstance;
}

Camera::Camera(Dimensions d): dimensions(d) {
	if (dimensions == Two) {
		transform.SetPosition(glm::vec3(0, 0, 10));
	}
	else {
		transform.SetPosition(glm::vec3());
	}
	
	lookDirection = glm::vec3(0, 0, -1.0f);

	Update();
}

void Camera::Update() {
	if (dimensions == Three) {
		lookDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		lookDirection.y = sin(glm::radians(pitch));
		lookDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	}
	
	

	view = glm::lookAt(transform.GetPosition(), transform.GetPosition() + lookDirection, glm::vec3(0.0f, 1.0f, 0.0f));

	if (dimensions == Two) {
		float xBounds = transform.GetScale().x;
		float yBounds = transform.GetScale().y;
		projection = glm::ortho(-xBounds, xBounds, -yBounds, yBounds,0.0f,100.0f);
	}
	else {
		projection = glm::perspective(glm::radians(45.f * transform.GetScale().x), transform.GetScale().x/ transform.GetScale().y, 0.1f, 100.0f);
	}
	
}



const glm::mat4* Camera::GetView() const{
	return &view;
}

const glm::mat4* Camera::GetProjection() const {
	return &projection;
}