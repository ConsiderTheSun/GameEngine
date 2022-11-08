#include "PlayerController2D.h"

void PlayerController2D::TransformSet(Transform* objT) {
	glm::vec3 oldPos = objT->GetPosition();
	if (Input::KeyDown(GLFW_KEY_W) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, 0.02f, 0);
		oldPos = objT->SetPosition(oldPos + delta);
	}
	if (Input::KeyDown(GLFW_KEY_S) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0, 0.02f, 0);
		oldPos = objT->SetPosition(oldPos - delta);
	}
	if (Input::KeyDown(GLFW_KEY_A) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0.02f, 0, 0);
		oldPos = objT->SetPosition(oldPos - delta);
	}
	if (Input::KeyDown(GLFW_KEY_D) == Input::State::Down) {
		glm::vec3 delta = glm::vec3(0.02f, 0, 0);
		oldPos = objT->SetPosition(oldPos + delta);
	}

}

void PlayerController2D::BodySet(PhysicsBody* objB) {
	bool moving = false;
	glm::vec3 newForce = glm::vec3();
	if (Input::KeyDown(GLFW_KEY_W) == Input::State::Down) {
		newForce += glm::vec3(0, 1, 0);
	}
	if (Input::KeyDown(GLFW_KEY_S) == Input::State::Down) {
		newForce -= glm::vec3(0, 1, 0);
	}
	if (Input::KeyDown(GLFW_KEY_A) == Input::State::Down) {
		newForce -= glm::vec3(1, 0, 0);
	}
	if (Input::KeyDown(GLFW_KEY_D) == Input::State::Down) {
		newForce += glm::vec3(1, 0, 0);
	}

	// sim drag
	if (!moving) {

	}

	if (glm::length2(objB->GetVelocity()) > MAX_SPEED) {
		objB->SetVelocity(MAX_SPEED * glm::normalize(objB->GetVelocity()));
	}
	else {
		objB->AddForce(ACC_SPEED * deltaTime * newForce );
	}

}
void PlayerController2D::PlayerControls() {
	

	if (Input::KeyDown(GLFW_KEY_ESCAPE) == Input::State::Down) {
		BetterSellingEngine::GetInstance()->End();
	}


	if (currentObject == NULL) return;

	Transform* objT = currentObject->GetComponent<Transform>();
	PhysicsBody* objB = currentObject->GetComponent<PhysicsBody>();
	if (objB) {
		//BodySet(objB);
		TransformSet(objT);
	}
	else {
		TransformSet(objT);
	}
	

	if (Input::KeyDown(GLFW_KEY_LEFT_SHIFT) == Input::State::Enter) {
		bool oldVal = BetterSellingEngine::GetInstance()->GetCollisionInteraction("Sad Layer", "Segy Layer");
		BetterSellingEngine::GetInstance()->SetCollisionInteraction("Sad Layer", "Segy Layer", !oldVal);
	}

	if (Input::KeyDown(GLFW_KEY_RIGHT_SHIFT) == Input::State::Enter) {
		bool oldVal = BetterSellingEngine::GetInstance()->GetCollisionInteraction("Sad Layer", "What Layer");
		BetterSellingEngine::GetInstance()->SetCollisionInteraction("Sad Layer", "What Layer", !oldVal);
	}




	if (Input::DeltaScroll() != 0) {
		glm::vec3 delta = (1.0f/5)*glm::vec3(Input::DeltaScroll(), Input::DeltaScroll(), 0.0);
		mainCamera->transform.SetScale(mainCamera->transform.GetScale() - delta);
	}


}

void PlayerController2D::UpdateObject() {
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

		if (dimentions == Camera::Dimensions::Two) {
			mainCamera->transform.SetPosition(glm::vec3(objPos.x, objPos.y, 10));
		}

		std::cout << "Current Object: " << currentObject->GetName() << std::endl;
	}
}

void PlayerController2D::MoveObjectFollow() {
	if (currentObject == NULL) return;


	//glm::vec3 camPos = mainCamera->transform.GetPosition();
	//currentObject->GetComponent<Transform>()->SetWorldPosition(glm::vec3(camPos.x,camPos.y,0));

	mainCamera->transform.SetPosition(currentObject->GetComponent<Transform>()->GetWorldPosition());

	Transform* transform = currentObject->transform;
	if (Input::KeyDown(GLFW_KEY_LEFT) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0, 0, 0.01);
		transform->SetRotation(oldRot + delta);
	}
	if (Input::KeyDown(GLFW_KEY_RIGHT) == Input::State::Down) {
		glm::vec3 oldRot = transform->GetRotation();
		glm::vec3 delta = glm::vec3(0, 0, 0.01);
		transform->SetRotation(oldRot - delta);
	}

	if (Input::KeyDown(GLFW_KEY_UP) == Input::State::Down) {
		glm::vec3 oldScale = transform->GetScale();
		glm::vec3 delta = glm::vec3(1.01, 1.01, 1);
		transform->SetScale(oldScale * delta);
	}
	if (Input::KeyDown(GLFW_KEY_DOWN) == Input::State::Down) {
		glm::vec3 oldScale = transform->GetScale();
		glm::vec3 delta = glm::vec3(0.99, 0.99, 1);
		transform->SetScale(oldScale * delta);
	}
}

// another way to check for collision
void PlayerController2D::SetColor() {

	for (GOM::Iterator gomItr = gom->begin(), end = gom->end(); gomItr != end; ++gomItr) {
		Sprite* sprite = gomItr->GetComponent<Sprite>();
		if (sprite) {
			sprite->SetColor(glm::vec3(1, 1, 1));
		}
	}

	std::vector<PhysicsBody*> colliders = Physics::GetInstance()->GetAllCollisions(currentObject);
	for (PhysicsBody* body : colliders) {
		Sprite* cSprite = body->gameObject->GetComponent<Sprite>();
		if (cSprite)
			cSprite->SetColor(glm::vec3(0.5, 1, 0.5));
	}
}

bool first = true;
void PlayerController2D::Update(float dt) {
	deltaTime = dt;
	PlayerControls();


	UpdateObject();
	

	MoveObjectFollow();

	// removes garfield (tests deletion)
	if (first) {
		first = false;

		GameObject* edge;

		edge = GOM::GetInstance()->Find("How, Hi are you?");
		if (edge) {
			edge->Destroy();
		}
		edge = GOM::GetInstance()->Find("Hi");
		if (edge) {
			edge->Destroy();
		}
		edge = GOM::GetInstance()->Find("Hi2");
		if (edge) {
			edge->Destroy();
		}
		edge = GOM::GetInstance()->Find("Hi3");
		if (edge) {
			edge->Destroy();
		}

		edge = GOM::GetInstance()->Find("Hi4");
		if (edge) {
			edge->Destroy();
		}
		edge = GOM::GetInstance()->Find("Hi5");
		if (edge) {
			edge->Destroy();
		}
		currentObject = NULL;
	}
}