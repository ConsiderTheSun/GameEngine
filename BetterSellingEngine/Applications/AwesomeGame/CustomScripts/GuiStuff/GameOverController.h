#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include "../../Scenes/GameScene.h"
#include "../../Scenes/MainMenuScene.h"


class GameOverController : public Script {
public:


	GameOverController(GameObject* go) : Script(go) { }

	void Update(float dt) override;

	void UpdateHover();

	void SetButtonSprites();

	void SetButtons(GameObject* restart, GameObject* mm, GameObject* quit);
private:
	GameObject* restartButton = nullptr;
	GameObject* mainMenuButton = nullptr;
	GameObject* quitButton = nullptr;

	double xPos, yPos;

	bool hoveringRestart = false;
	bool hoveringMainMenu = false;
	bool hoveringQuit = false;
};