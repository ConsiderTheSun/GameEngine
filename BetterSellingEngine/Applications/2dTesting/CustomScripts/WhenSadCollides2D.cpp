#include "WhenSadCollides2D.h"

void WhenSadCollides2D::Update(float dt) {
	
}
#include <glm/glm/gtx/string_cast.hpp>
void WhenSadCollides2D::OnCollisionEnter(CollisionEvent* e) {
	GameObject* collisionObject = e->collisionObject;
	std::cout << "Enter Collision w/: " << collisionObject->GetName() << std::endl;
	std::cout << "normal: " << glm::to_string(e->normal) << ", depth: " << e->depth << std::endl;
	Sprite* sprite = collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(0.5, 1, 0.5));
	}

	//GameObject::Destroy(collisionObject);

	glm::vec3 move = 2 * e->depth * e->normal;
	Transform* t = e->collisionObject->GetComponent<Transform>();
	t->SetPosition(t->GetPosition() + move);

	//Transform* thisT = gameObject->GetComponent<Transform>();
	//thisT->SetPosition(thisT->GetPosition() - move);
}
void WhenSadCollides2D::OnCollision(CollisionEvent* e) {
	/*
	// can set rotation or position directly
	Transform* collisionT = collisionObject->GetComponent<Transform>();
	collisionT->SetRotation(collisionT->GetRotation() - glm::vec3(0, 0, 0.002f));
	*/

	glm::vec3 move = 4 * e->depth * e->normal;
	Transform* t = e->collisionObject->GetComponent<Transform>();
	t->SetPosition(t->GetPosition() + move);
	
}

void WhenSadCollides2D::OnCollisionExit(CollisionEvent* e) {
	std::cout << "Exit Collision w/: " << e->collisionObject->GetName() << std::endl;
	Sprite* sprite = e->collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(1, 1, 1));
	}

	
}
