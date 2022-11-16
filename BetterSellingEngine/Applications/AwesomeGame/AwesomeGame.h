#pragma once
#include "../../Engine/engineIncludes.h"
#include "../../Engine/BetterSellingEngine.h"

#include "CustomScripts/PlayerController.h"
#include "CustomScripts/CameraController.h"
#include "CustomScripts/GameController.h"
#include "CustomScripts/EnemyManager.h"

#include "EntityFactory.h"

class AwesomeGame{
public:
	void Setup();
	void Start();
private:
	BetterSellingEngine* bse;

	void CreateWindow();

	void CreateEnvironment();

	GameObject* CreatePlayer();

	void GameControllerSetup();

	void CameraSetup(GameObject* followGO);

	void InputSetup();

};