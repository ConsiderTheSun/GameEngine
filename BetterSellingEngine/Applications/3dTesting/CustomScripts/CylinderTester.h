#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"
#include <glm/glm/gtx/string_cast.hpp>

class CylinderTester : public Script {
public:

	int currentObjectIndex = 0;

	CylinderTester(GameObject* go) : Script(go) {}

	void Update(float dt) override;

	void OnCollisionEnter(CollisionEvent* e) override;
	void OnCollision(CollisionEvent* e) override;
	void OnCollisionExit(CollisionEvent* e) override;
};