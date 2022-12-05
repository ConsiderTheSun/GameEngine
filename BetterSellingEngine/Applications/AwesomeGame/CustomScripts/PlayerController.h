#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include "../EntityFactory.h"

#include "../Scenes/GameOverScene.h"


class EnemyManager;

class PlayerController : public Script {
public:
	const float MASS = 2;

	int victoryRequirement = 1;
	int victoryPoints = 0;

	glm::vec3 playerColor;

	PlayerController(GameObject* go);

	void Move(float dt);
	void Shoot(float dt);
	void UpdateInvincibility(float dt);

	void TakeDamage();

	void Update(float dt) override;

	void OnCollisionEnter(CollisionEvent* e) override;
	void OnCollision(CollisionEvent* e) override;
	void OnCollisionExit(CollisionEvent* e) override;

	static GameObject* GetCurrentPlatform() { return currentPlatform; }
	static GameObject* MostRecentPlatform() { 
		if(currentPlatform) return currentPlatform; 
		return previousPlatform;
	}

private:

	static GameObject* currentPlatform;
	static GameObject* previousPlatform;


	const glm::vec3 DAMAGE_COLOR = glm::vec3(1, 0, 0);

	const float SPEED = 3;
	const float SHOT_RATE = 0.5;
	const float SHOT_SPEED = 5.0f;

	const float INVINCIBILITY_TIME = 0.2f;

	const float FALL_MULTIPLYER = 5;

	

	bool falling = false;

	int jumpCount = 1;

	float invincibilityCounter;
	float shootCooldown = SHOT_RATE;

	bool invincible = false;

	int health = 3;

	Transform* playerTransform;
	PhysicsBody* playerPhysicsBody;

};
