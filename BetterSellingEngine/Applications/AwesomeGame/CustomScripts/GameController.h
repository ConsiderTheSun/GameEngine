#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class GameController : public Script {
public:


	GameController(GameObject* go) : Script(go) {}

	void Update(float dt) override;


};