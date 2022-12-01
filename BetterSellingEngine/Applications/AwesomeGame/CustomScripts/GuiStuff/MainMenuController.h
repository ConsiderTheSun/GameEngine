#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include "../../Scenes/GameScene.h"


class MainMenuController : public Script {
public:


	MainMenuController(GameObject* go) : Script(go) { }

	void Update(float dt) override;

	void UpdateHover();

	void SetButtonSprites();

	GameObject* title = nullptr;

	GameObject* startButton = nullptr;
	GameObject* howToPlayButton = nullptr;
	GameObject* quitButton = nullptr;
	GameObject* backButton = nullptr;

	GameObject* instructions = nullptr;

private:
	

	double xPos, yPos;

	bool hoveringStart = false;
	bool hoveringHowToPlay = false;
	bool hoveringQuit = false;
	bool hoveringBack = false;
};