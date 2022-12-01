#include "CameraController.h"

void CameraController::Update(float dt) {

	// gets the current zoom
	currentDistance -= Input::DeltaScroll();
	if (currentDistance < 2) currentDistance = 2;
	else if (currentDistance > 20) currentDistance = 20;

	//sets the camera angle
	float followRotation = followTransform->GetWorldRotation().z;
	mainCamera->yaw = -180 * followRotation / 3.14 - 90;
	mainCamera->pitch -= 0.2 * Input::DeltaMouse().y;

	if (mainCamera->pitch > 0.0f) mainCamera->pitch = 0.0f;
	if (mainCamera->pitch < -89.0f) mainCamera->pitch = -89.0f;


	// determines the camera position based on rotation of camera and follow obj
	glm::vec3 camPos = 
		glm::vec3(sin(followRotation) * cos(glm::radians(mainCamera->pitch)),
				  -sin(glm::radians(mainCamera->pitch)),
				  cos(followRotation) * cos(glm::radians(mainCamera->pitch)));

	
	mainCamera->transform.SetPosition(followTransform->GetWorldPosition() + currentDistance* camPos);

}