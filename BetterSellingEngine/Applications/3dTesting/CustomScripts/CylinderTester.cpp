#include "CylinderTester.h"

void CylinderTester::Update(float dt) {

}

void CylinderTester::OnCollisionEnter(CollisionEvent* e) {
	std::cout << "Enter Collision w/: " << e->collisionObject->GetName() << std::endl;
	std::cout << "normal: " <<glm::to_string(e->normal) << std::endl;
	Sprite* sprite = e->collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(0.5, 1, 0.5));
	}

}
void CylinderTester::OnCollision(CollisionEvent* e) {
	Transform* t = e->collisionObject->GetComponent<Transform>();
	glm::vec3 pos = t->GetWorldPosition();
	glm::vec3 newPos = pos + e->normal * e->depth;
	t->SetWorldPosition(newPos);

}

void CylinderTester::OnCollisionExit(CollisionEvent* e) {
	std::cout << "Exit Collision w/: " << e->collisionObject->GetName() << std::endl;
	Sprite* sprite = e->collisionObject->GetComponent<Sprite>();
	if (sprite) {
		sprite->SetColor(glm::vec3(1, 1, 1));
	}
}