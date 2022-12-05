#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class Enemy : public Script {
public:
	Enemy(GameObject* go) : Script(go) { }

	virtual void TakeDamage(int damage);
protected:
	int health = 3;
};