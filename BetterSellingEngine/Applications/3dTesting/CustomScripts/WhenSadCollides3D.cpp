#include "WhenSadCollides3D.h"

void WhenSadCollides3D::Update(float dt) {
	
}

void WhenSadCollides3D::OnCollisionEnter(CollisionEvent* e) {
	std::cout << "Enter Collision w/: " << e->collisionObject->GetName() << std::endl;
	Sprite* sprite = e->collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(0.5, 1, 0.5));
	}

	//GameObject::Destroy(collisionObject);
}
void WhenSadCollides3D::OnCollision(CollisionEvent* e) {
	/*
	// can set rotation or position directly
	Transform* collisionT = collisionObject->GetComponent<Transform>();
	collisionT->SetRotation(collisionT->GetRotation() - glm::vec3(0, 0, 0.002f));
	*/
	
}

void WhenSadCollides3D::OnCollisionExit(CollisionEvent* e) {
	std::cout << "Exit Collision w/: " << e->collisionObject->GetName() << std::endl;
	Sprite* sprite = e->collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(1, 1, 1));
	}

	
}
