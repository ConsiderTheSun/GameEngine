#pragma once
#include "../../Engine/engineIncludes.h"
#include "../../Engine/BetterSellingEngine.h"

#include "CustomScripts/PlayerController.h"
#include "CustomScripts/CameraController.h"
#include "CustomScripts/GameController.h"
#include "CustomScripts/EnemyManager.h"
#include "CustomScripts/PlatformManager.h"

#include "EntityFactory.h"

#include "Scenes/MainMenuScene.h"

class AwesomeGame{
public:
	void Setup();
	void Start();
private:
	BetterSellingEngine* bse;

	void CreateWindow();
};