#include "PlayerController.h"

void PlayerController::Update(float dt) {
	
	float rotationSpeed = 1.0 / 500;
	glm::vec3 deltaRotation = glm::vec3(0, 0, -rotationSpeed*Input::DeltaMouse().x);
	playerTransform->SetRotation(playerTransform->GetRotation() + deltaRotation);

	glm::vec3 deltaPos = glm::vec3(0, 0, 0);
	if (Input::KeyDown(GLFW_KEY_W) == Input::State::Down) {
		deltaPos = playerTransform->Up();
	}
	if (Input::KeyDown(GLFW_KEY_S) == Input::State::Down) {
		deltaPos += playerTransform->Down();
	}

	if (Input::KeyDown(GLFW_KEY_A) == Input::State::Down) {
		deltaPos += playerTransform->Left();
	}
	if (Input::KeyDown(GLFW_KEY_D) == Input::State::Down) {
		deltaPos += playerTransform->Right();
	}

	if (deltaPos.x * deltaPos.x + deltaPos.z * deltaPos.z > 0) {
		deltaPos = SPEED * dt * glm::normalize(deltaPos);
	}

	playerTransform->SetPosition(playerTransform->GetPosition() + deltaPos);

}


void PlayerController::OnCollisionEnter(CollisionEvent* e) {
	std::cout << "Enter Collision w/: " << e->collisionObject->GetName() << std::endl;
	Sprite* sprite = e->collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(0.5, 0, 0.5));
	}

	//GameObject::Destroy(e->collisionObject);
}

void PlayerController::OnCollisionExit(CollisionEvent* e) {
	std::cout << "Exit Collision w/: " << e->collisionObject->GetName() << std::endl;
	Sprite* sprite = e->collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(1, 1, 1));
	}


}