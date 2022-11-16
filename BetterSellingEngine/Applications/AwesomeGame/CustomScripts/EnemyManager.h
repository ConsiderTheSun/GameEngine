#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include "../EntityFactory.h"
class EnemyManager : public Script {
public:


	EnemyManager(GameObject* go) : Script(go) { }

	void Update(float dt) override;

private:

	void SpawnEnemy(glm::vec3 position);

};