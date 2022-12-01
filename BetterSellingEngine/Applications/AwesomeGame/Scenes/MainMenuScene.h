#pragma once
#include "../../Engine/engineIncludes.h"

#include "../CustomScripts/GuiStuff/MainMenuController.h"
#include "../CustomScripts/PlayerController.h"
#include "../AwesomeGame.h"
class MainMenuScene : public Scene {
	BetterSellingEngine* bse = BetterSellingEngine::GetInstance();

	GameObject* title;

	GameObject* startButton;
	GameObject* howToPlayButton;
	GameObject* quitButton;
	GameObject* backButton;
	
	GameObject* instructions;
	void LoadScene() override;

	void SpawnTitle();
	void SpawnButtons();

	void SpawnInstructions();

	void SetupInteraction();

};