#include "GameController.h"

void GameController::Update(float dt) {
	if (Input::KeyDown(GLFW_KEY_ESCAPE) == Input::State::Down) {
		BetterSellingEngine::GetInstance()->End();
	}
}


