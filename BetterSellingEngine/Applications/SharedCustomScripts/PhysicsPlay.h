#pragma once

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class PhysicsPlay : public Script {
public:
	Physics* physicsSystem = Physics::GetInstance();

	PhysicsBody* body;

	bool noGravity = true;

	PhysicsPlay(GameObject* go);

	void Update(float dt) override;
	void OnCollisionEnter(CollisionEvent* e) override;
	void OnCollision(CollisionEvent* e) override;
	void OnCollisionExit(CollisionEvent* e) override;
};