#pragma once
#include <list>
#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include "../EntityFactory.h"

#include "PlayerController.h"
#include "PlatformManager.h"
class EnemyManager : public Script {
public:

	EnemyManager(GameObject* go) : Script(go) { }

	void Update(float dt) override;


	static GameObject* playerGO;
	static PlatformManager* platformManager;
	static void SetPlayerGameObject(GameObject* go) { playerGO = go; }
	static void SetPlatformManager(PlatformManager* pm) { platformManager = pm; }

	static void RemoveEnemy(GameObject* enemyGO);

private:
	const float SPAWN_RATE = 1;
	const int MAX_ENEMIES = 20;

	float spawnCountdown = SPAWN_RATE;
	void SpawnFollowEnemy();
	void ClampEnemyCount();
	static std::list<GameObject*> enemyList;

};