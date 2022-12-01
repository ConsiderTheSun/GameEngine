#include "MainMenuController.h"

void MainMenuController::Update(float dt) {
	Input::GetMousePos(xPos, yPos);

	if (Input::KeyDown(GLFW_KEY_ESCAPE) == Input::State::Down) {
		BetterSellingEngine::GetInstance()->End();
	}

	if (Input::KeyDown(GLFW_MOUSE_BUTTON_LEFT) == Input::State::Enter) {
		if (hoveringStart) {
			BetterSellingEngine::GetInstance()->ChangeScene(new GameScene());
		}
		else if (hoveringHowToPlay) {
			instructions->Enable();
			backButton->Enable();
			title->Disable();
			startButton->Disable();
			howToPlayButton->Disable();
			quitButton->Disable();
		}
		else if(hoveringQuit) {
			BetterSellingEngine::GetInstance()->End();
		}
		else if (hoveringBack) {
			instructions->Disable();
			backButton->Disable();
			title->Enable();
			startButton->Enable();
			howToPlayButton->Enable();
			quitButton->Enable();
		}
	}

	

	UpdateHover();
	SetButtonSprites();
}

void MainMenuController::UpdateHover() {
	hoveringStart = CollisionTest::PointInOBB(glm::vec3(xPos, yPos, 0),
		startButton->GetComponent<PhysicsBody>());
	hoveringHowToPlay = CollisionTest::PointInOBB(glm::vec3(xPos, yPos, 0),
		howToPlayButton->GetComponent<PhysicsBody>());
	hoveringQuit = CollisionTest::PointInOBB(glm::vec3(xPos, yPos, 0),
		quitButton->GetComponent<PhysicsBody>());
	hoveringBack = CollisionTest::PointInOBB(glm::vec3(xPos, yPos, 0),
		backButton->GetComponent<PhysicsBody>());

}

void MainMenuController::SetButtonSprites() {
	if (hoveringStart)
		startButton->GetComponent<Sprite>()->SetColor(glm::vec3(0.7, 0.7, 0.7));
	else
		startButton->GetComponent<Sprite>()->SetColor(glm::vec3(1, 1, 1));

	if (hoveringHowToPlay)
		howToPlayButton->GetComponent<Sprite>()->SetColor(glm::vec3(0.7, 0.7, 0.7));
	else
		howToPlayButton->GetComponent<Sprite>()->SetColor(glm::vec3(1, 1, 1));

	if (hoveringQuit)
		quitButton->GetComponent<Sprite>()->SetColor(glm::vec3(0.7, 0.7, 0.7));
	else
		quitButton->GetComponent<Sprite>()->SetColor(glm::vec3(1, 1, 1));

	if (hoveringBack)
		backButton->GetComponent<Sprite>()->SetColor(glm::vec3(0.7, 0.7, 0.7));
	else
		backButton->GetComponent<Sprite>()->SetColor(glm::vec3(1, 1, 1));
}

