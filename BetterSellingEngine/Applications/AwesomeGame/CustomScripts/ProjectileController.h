#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include "../EntityFactory.h"
#include "Enemy/Enemy.h"

class ProjectileController : public Script {
public:


	ProjectileController(GameObject* go) : Script(go) { }

	void Update(float dt) override;
	void OnCollisionEnter(CollisionEvent* e) override;
private:


};