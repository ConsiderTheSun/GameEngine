#include "PlayerController3D.h"

void PlayerController3D::PlayerControls3D(float dt) {
	Camera* mainCamera = Camera::MainCamera();

	mainCamera->yaw += 0.2 * Input::DeltaMouse().x;
	mainCamera->pitch += 0.2 * Input::DeltaMouse().y;

	if (mainCamera->pitch > 89.0f)
		mainCamera->pitch = 89.0f;
	if (mainCamera->pitch < -89.0f)
		mainCamera->pitch = -89.0f;

	if (Input::KeyDown(GLFW_KEY_ESCAPE) == Input::State::Down) {
		BetterSellingEngine::GetInstance()->End();
	}

	glm::vec3 oldPos = mainCamera->transform.GetPosition();
	float speed = 3 * dt;
	if (Input::KeyDown(GLFW_KEY_W) == Input::State::Down) {
		glm::vec3 delta = speed * mainCamera->lookDirection;
		oldPos = mainCamera->transform.SetPosition(oldPos + delta);
	}
	if (Input::KeyDown(GLFW_KEY_S) == Input::State::Down) {
		glm::vec3 delta = speed * mainCamera->lookDirection;
		oldPos = mainCamera->transform.SetPosition(oldPos - delta);
	}
	if (Input::KeyDown(GLFW_KEY_A) == Input::State::Down) {
		glm::vec3 delta = speed * glm::normalize(glm::cross(mainCamera->lookDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
		oldPos = mainCamera->transform.SetPosition(oldPos - delta);
	}
	if (Input::KeyDown(GLFW_KEY_D) == Input::State::Down) {
		glm::vec3 delta = speed * glm::normalize(glm::cross(mainCamera->lookDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
		oldPos = mainCamera->transform.SetPosition(oldPos + delta);
	}
	if (Input::KeyDown(GLFW_KEY_SPACE) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, speed, 0);
		oldPos = mainCamera->transform.SetPosition(oldPos + delta);
	}
	if (Input::KeyDown(GLFW_KEY_LEFT_SHIFT) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, speed, 0);
		oldPos = mainCamera->transform.SetPosition(oldPos - delta);
	}

	if (Input::DeltaScroll() != 0) {
		glm::vec3 delta = (1.0f / 5) * glm::vec3(Input::DeltaScroll(), Input::DeltaScroll(), 0.0);
		mainCamera->transform.SetScale(mainCamera->transform.GetScale() - delta);
	}
}


void PlayerController3D::UpdateObject() {
	bool indexChange = false;
	if (Input::KeyDown(GLFW_KEY_LEFT_BRACKET) == Input::State::Enter) {
		--currentObjectIndex;
		indexChange = true;
	}
	if (Input::KeyDown(GLFW_KEY_RIGHT_BRACKET) == Input::State::Enter) {
		++currentObjectIndex;
		indexChange = true;
	}
	if(currentObject == NULL){
		indexChange = true;
	}
	if (!indexChange) return;

	GameObject* oldObject = currentObject;
	int i = 0;
	bool found = false;
	for (GOM::Iterator gomItr = gom->begin(), end = gom->end(); gomItr != end; ++gomItr,++i) {
		if (i == currentObjectIndex) {
			if (&*gomItr == gameObject) {
				++currentObjectIndex;
			}
			else {
				currentObject = &*gomItr;
				found = true;
				break;
			}
			
		}
	}
	if (!found) {
		if (gom->begin() != gom->end()) {
			currentObject = &*gom->begin();
			currentObjectIndex = 0;
		}
		else {
			currentObject = NULL;
			currentObjectIndex = 0;
		}
	}
	
	if (currentObject != oldObject && currentObject != NULL) {

		glm::vec3 objPos = currentObject->GetComponent<Transform>()->GetWorldPosition();

		std::cout << "Current Object: " << currentObject->GetName() << std::endl;
	}
}

void PlayerController3D::MoveObjectSeperate() {
	Transform* transform = currentObject->GetComponent<Transform>();
	glm::vec3 oldPos = transform->GetPosition();
	if (Input::KeyDown(GLFW_KEY_I) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, 0.02f, 0);
		oldPos = transform->SetPosition(oldPos + delta);
	}
	if (Input::KeyDown(GLFW_KEY_K) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, 0.02f, 0);
		oldPos = transform->SetPosition(oldPos - delta);
	}
	if (Input::KeyDown(GLFW_KEY_J) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0.02f, 0, 0);
		oldPos = transform->SetPosition(oldPos - delta);
	}
	if (Input::KeyDown(GLFW_KEY_L) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0.02f, 0, 0);
		oldPos = transform->SetPosition(oldPos + delta);
	}
	if (Input::KeyDown(GLFW_KEY_O) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, 0, 0.02f);
		oldPos = transform->SetPosition(oldPos - delta);
	}
	if (Input::KeyDown(GLFW_KEY_P) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, 0, 0.02f);
		oldPos = transform->SetPosition(oldPos + delta);
	}

	if (Input::KeyDown(GLFW_KEY_UP) == Input::State::Down) {
		glm::vec3 oldScale = transform->GetScale();
		glm::vec3 delta = glm::vec3(1.01, 1.01, 1.01);
		transform->SetScale(oldScale * delta);
	}
	if (Input::KeyDown(GLFW_KEY_DOWN) == Input::State::Down) {
		glm::vec3 oldScale = transform->GetScale();
		glm::vec3 delta = glm::vec3(0.99, 0.99, 0.99);
		transform->SetScale(oldScale * delta);
	}


	if (Input::KeyDown(GLFW_KEY_T) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0, 0, 0.01);
		transform->SetRotation(oldRot + delta);
	}
	if (Input::KeyDown(GLFW_KEY_Y) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0, 0, 0.01);
		transform->SetRotation(oldRot - delta);
	}
	if (Input::KeyDown(GLFW_KEY_G) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0, 0.01, 0);
		transform->SetRotation(oldRot + delta);
	}
	if (Input::KeyDown(GLFW_KEY_H) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0, 0.01, 0);
		transform->SetRotation(oldRot - delta);
	}
	if (Input::KeyDown(GLFW_KEY_B) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0.01, 0, 0);
		transform->SetRotation(oldRot + delta);
	}
	if (Input::KeyDown(GLFW_KEY_N) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0.01, 0, 0);
		transform->SetRotation(oldRot - delta);
	}
}

void PlayerController3D::Update(float dt) {

	PlayerControls3D(dt);

	UpdateObject();
	
	MoveObjectSeperate();
}