#include "GameOverScene.h"
void GameOverScene::LoadScene() {
	bse->RegisterEvent<SceneChangeEvent>();

	if (win) {
		bse->SetBackgroundColor(glm::vec3(0.988, 0.761, 0));
	}
	else {
		bse->SetBackgroundColor(glm::vec3(0.4f, 0.0f, 0.0f));
	}

	SpawnTitle();
	SpawnButtons();
	SetupInteraction();
}

void GameOverScene::SpawnTitle() {
	GameObject* title = new GameObject();
	Sprite* sprite = title->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	if (win) {
		sprite->SetMaterial("./assets/youWin.png", false);
	}
	else {
		sprite->SetMaterial("./assets/gameOver.png", false);
	}

	Transform* transform = title->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, 0.5, 0));
	transform->SetScale(glm::vec3(1.5, 0.5, 1));

	bse->AddGameObject(title);
}


void GameOverScene::SpawnButtons() {
	restartButton = new GameObject();

	Sprite* sprite = restartButton->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/restart.png", true);

	PhysicsBody* body = restartButton->AddComponent<PhysicsBody>();
	body->SetOBB();

	Transform* transform = restartButton->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, -0.05, 0));
	transform->SetScale(glm::vec3(1, 0.25, 1));

	bse->AddGameObject(restartButton);

	mainMenuButton = new GameObject();
	sprite = mainMenuButton->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/mainMenu.png", true);
	body = mainMenuButton->AddComponent<PhysicsBody>();
	body->SetOBB();

	transform = mainMenuButton->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, -0.4, 0));
	transform->SetScale(glm::vec3(1, 0.25, 1));

	bse->AddGameObject(mainMenuButton);

	quitButton = new GameObject();
	sprite = quitButton->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/quit.png", true);

	body = quitButton->AddComponent<PhysicsBody>();
	body->SetOBB();

	transform = quitButton->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, -0.75, 0));
	transform->SetScale(glm::vec3(1, 0.25, 1));

	bse->AddGameObject(quitButton);
}

void GameOverScene::SetupInteraction() {
	Input::AddTracking(1, GLFW_MOUSE_BUTTON_LEFT);
	Input::AddTracking(1, GLFW_KEY_ESCAPE);

	GameObject* holderOfTheScript = new GameObject();

	GameOverController* mmc = holderOfTheScript->AddComponent<GameOverController>();

	mmc->SetButtons(restartButton, mainMenuButton, quitButton);
	bse->AddGameObject(holderOfTheScript);

}
