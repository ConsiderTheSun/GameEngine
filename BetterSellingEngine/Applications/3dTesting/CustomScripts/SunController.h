#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class SunController : public Script {
	BetterSellingEngine* bse = BetterSellingEngine::GetInstance();
public:

	SunController(GameObject* go) : Script(go) {}

	void Update(float dt) override;
};