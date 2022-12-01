#include "GameOverController.h"

void GameOverController::SetButtons(GameObject* restart, GameObject* mm, GameObject* quit) {
	restartButton = restart;
	mainMenuButton = mm;
	quitButton = quit;
}


void GameOverController::Update(float dt) {
	Input::GetMousePos(xPos, yPos);

	if (Input::KeyDown(GLFW_KEY_ESCAPE) == Input::State::Down) {
		BetterSellingEngine::GetInstance()->End();
	}

	if (Input::KeyDown(GLFW_MOUSE_BUTTON_LEFT) == Input::State::Enter) {
		if (hoveringRestart) {
			BetterSellingEngine::GetInstance()->ChangeScene(new GameScene());
		}
		else if (hoveringMainMenu) {
			BetterSellingEngine::GetInstance()->ChangeScene(new MainMenuScene());
		}
		else if (hoveringQuit) {
			BetterSellingEngine::GetInstance()->End();
		}
	}



	UpdateHover();
	SetButtonSprites();
}

void GameOverController::UpdateHover() {
	hoveringRestart = CollisionTest::PointInOBB(glm::vec3(xPos, yPos, 0),
		restartButton->GetComponent<PhysicsBody>());
	hoveringMainMenu = CollisionTest::PointInOBB(glm::vec3(xPos, yPos, 0),
		mainMenuButton->GetComponent<PhysicsBody>());
	hoveringQuit = CollisionTest::PointInOBB(glm::vec3(xPos, yPos, 0),
		quitButton->GetComponent<PhysicsBody>());

}

void GameOverController::SetButtonSprites() {
	if (hoveringRestart)
		restartButton->GetComponent<Sprite>()->SetColor(glm::vec3(0.7, 0.7, 0.7));
	else
		restartButton->GetComponent<Sprite>()->SetColor(glm::vec3(1, 1, 1));

	if (hoveringMainMenu)
		mainMenuButton->GetComponent<Sprite>()->SetColor(glm::vec3(0.7, 0.7, 0.7));
	else
		mainMenuButton->GetComponent<Sprite>()->SetColor(glm::vec3(1, 1, 1));

	if (hoveringQuit)
		quitButton->GetComponent<Sprite>()->SetColor(glm::vec3(0.7, 0.7, 0.7));
	else
		quitButton->GetComponent<Sprite>()->SetColor(glm::vec3(1, 1, 1));
}

