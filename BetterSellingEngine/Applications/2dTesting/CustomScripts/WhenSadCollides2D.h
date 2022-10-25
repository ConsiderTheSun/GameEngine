#pragma once

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class WhenSadCollides2D : public Script {
public:
	WhenSadCollides2D(GameObject* go) : Script(go) {}

	void Update(float dt) override;
	void OnCollisionEnter(CollisionEvent* e) override;
	void OnCollision(CollisionEvent* e) override;
	void OnCollisionExit(CollisionEvent* e) override;
};