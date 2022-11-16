#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class PlayerController : public Script {
public:


	PlayerController(GameObject* go) : Script(go) { playerTransform = gameObject->GetComponent<Transform>(); }

	void Update(float dt) override;

	void OnCollisionEnter(CollisionEvent* e) override;
	void OnCollisionExit(CollisionEvent* e) override;

private:
	 const float SPEED = 3;

	 Transform* playerTransform;

};