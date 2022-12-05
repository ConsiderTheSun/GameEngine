#include "EnemyManager.h"
#include "Enemy/Follower.h"

#define _USE_MATH_DEFINES
#include <math.h>

GameObject* EnemyManager::playerGO = nullptr;
PlatformManager* EnemyManager::platformManager = nullptr;

std::list<GameObject*> EnemyManager::enemyList = std::list<GameObject*>();

void EnemyManager::Update(float dt) {
	spawnCountdown -= dt;

	if (spawnCountdown < 0) {
		spawnCountdown = SPAWN_RATE;
		SpawnFollowEnemy();
	}
	
	/*if (Input::KeyDown(GLFW_MOUSE_BUTTON_RIGHT) == Input::State::Enter) {
		for(int i=0;i<10;++i)
			SpawnFollowEnemy();
	}*/
	
}

void EnemyManager::SpawnFollowEnemy() {
	GameObject* platform = PlayerController::GetCurrentPlatform();
	if (platform) {
		glm::vec3 playerPos = playerGO->transform->GetWorldPosition();
		glm::vec3 enemyPos;
		int attempts = 0;
		bool illegalPosition;
		do {
			// makes sure there are no infinite loops (if platform is too small)
			if (++attempts > 20) return;

			float theta = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * M_PI)));
			Transform* t = platform->GetComponent<Transform>();
			enemyPos = t->GetWorldPosition();
			enemyPos.y += t->GetScale().z / 2 + 0.5f;

			float dist = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.9f * t->GetScale().x / 2)));
			enemyPos += dist * glm::vec3(cos(theta), 0, sin(theta));
			//enemyPos += 0.9f * t->GetScale().x / 2 * glm::vec3(cos(theta), 0, sin(theta));
			illegalPosition = 20 > abs(glm::dot(enemyPos - playerPos, enemyPos - playerPos));
			illegalPosition = illegalPosition || !platformManager->noIntersections(platform, enemyPos, 0.5f);
		} while (illegalPosition);

		//if spawned inside of another platform, displace it
		GameObject* enemyGO;
		if (enemyList.size() < MAX_ENEMIES) {
			enemyGO = EntityFactory::MakeI("Enemy", "Enemy Layer", enemyPos, glm::vec3(0.0, 1, 0.0));

			PhysicsBody* entityB = enemyGO->GetChild(0)->AddComponent<PhysicsBody>();
			enemyGO->GetChild(0)->SetLayer("Enemy Layer");
			entityB->SetSphere();
			entityB->SetHasGravity(false);

			Follower* follower = enemyGO->AddComponent<Follower>();
			follower->SetFollow(playerGO);
			follower->SetPlatform(platform);
		}
		else {
			enemyGO = enemyList.front();
			enemyList.pop_front();

			Follower* follower = enemyGO->GetComponent<Follower>();
			follower->SetPlatform(platform);
			enemyGO->transform->SetPosition(enemyPos);
		}
		enemyList.push_back(enemyGO);
	}
	ClampEnemyCount();
}


void EnemyManager::ClampEnemyCount() {
	while (enemyList.size() > MAX_ENEMIES) {
		GameObject* oldestEnemy = enemyList.front();
		enemyList.pop_front();

		//std::cout << "oldest: " << oldestEnemy->GetName() << std::endl;

		GameObject::Destroy(oldestEnemy);
		//std::cout << "sent destroy" << std::endl;
	}
}


void EnemyManager::RemoveEnemy(GameObject* enemyGO) {
	std::list<GameObject*>::iterator eItr = enemyList.begin();
	for (; eItr != enemyList.end(); ++eItr) {
		if (*eItr == enemyGO) {
			enemyList.erase(eItr);
			GameObject::Destroy(enemyGO);
			return;
		}
	}
	
}
