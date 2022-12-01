#pragma once
#include "../../Engine/engineIncludes.h"

#include "../AwesomeGame.h"
#include "../CustomScripts/PlatformManager.h"

class GameScene : public Scene {
	GameObject* playerGO = nullptr;
	PlatformManager* platformManager = nullptr;
	BetterSellingEngine* bse = BetterSellingEngine::GetInstance();

	void LoadScene() override;

	void LetThereBeLight();

	void LayerSetup();

	void SpawnPlatform(glm::vec3 position, float scale, glm::vec3 color = glm::vec3(0.5, 0, 0.5));
	void CreateEnvironment();

	void MakeASphere(glm::vec3 position, float scale, glm::vec3 color = glm::vec3(0.988, 0.761, 0));
	void SpheresLikeThese();

	void CreatePlayer();

	

	void GameControllerSetup();

	void CameraSetup(GameObject* followGO);

	void InputSetup();
};