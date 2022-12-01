#include "Follower.h"


void Follower::Update(float dt) {

	if (PlayerController::MostRecentPlatform() == platformGO) {
		glm::vec3 currentPos = gameObject->transform->GetPosition();
		glm::vec3 playerPos = followTransform->GetPosition();

		glm::vec3 direction = playerPos - currentPos;
		direction.y = 0;
		direction=glm::normalize(direction);
		glm::vec3 newPos = currentPos + SPEED * direction;

		// check bounds
		glm::vec3 diff = newPos - platformPos;
		float squareDist = diff.x * diff.x + diff.y * diff.y + diff.z * diff.z;
		if (squareDist > maxDistance * maxDistance) {
			newPos = maxDistance * glm::normalize(diff) + platformPos;
		}
		gameObject->transform->SetPosition(newPos);
	}
	
}

void Follower::OnCollision(CollisionEvent* e) {

	if (e->collisionObject->GetLayerName() == "Enemy Layer") {
		glm::vec3 offset = gameObject->transform->GetPosition() - e->depth * e->normal;
		gameObject->transform->SetPosition(offset);
	}
}

void Follower::SetPlatform(GameObject* go) {
	platformGO = go;
	platformPos = go->transform->GetWorldPosition();
	platformPos.y = gameObject->transform->GetWorldPosition().y;
	maxDistance = go->transform->GetWorldScale().x / 2 -gameObject->transform->GetWorldScale().x / 2;
}
