#pragma once
#include "../../Engine/engineIncludes.h"

#include "../CustomScripts/GuiStuff/GameOverController.h"
#include "../AwesomeGame.h"

class GameOverScene : public Scene {
public:
	bool win = false;
private:

	BetterSellingEngine* bse = BetterSellingEngine::GetInstance();

	GameObject* restartButton;
	GameObject* mainMenuButton;
	GameObject* quitButton;

	void LoadScene() override;

	void SpawnTitle();
	void SpawnButtons();

	void SetupInteraction();

};