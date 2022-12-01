#include "ProjectileController.h"

void ProjectileController::Update(float dt) {

	if (gameObject->transform->GetPosition().y < -2) {
		GameObject::Destroy(gameObject);
	}
}

void ProjectileController::OnCollisionEnter(CollisionEvent* e) {

	GameObject* cObj = e->collisionObject;
	if (cObj->GetLayerName() == "Enemy Layer") {
		Enemy* enemy = cObj->GetComponent<Enemy>();
		if (enemy) {
			enemy->TakeDamage(1);
		}
	}

	GameObject::Destroy(gameObject);
}
