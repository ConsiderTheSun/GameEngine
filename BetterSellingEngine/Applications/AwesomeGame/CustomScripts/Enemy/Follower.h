#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include "Enemy.h"

#include "../PlayerController.h"

class Follower : public Enemy {
public:


	Follower(GameObject* go) : Enemy(go) { health = 2; }

	void Update(float dt) override;

	void OnCollision(CollisionEvent* e) override;

	void SetFollow(GameObject* go) { followTransform = go->transform; }

	void SetPlatform(GameObject* go);
private:
	GameObject* platformGO = nullptr;

	Transform* followTransform;

	const float SPEED = 1.0f / 100;

	glm::vec3 platformPos;
	float maxDistance;

};