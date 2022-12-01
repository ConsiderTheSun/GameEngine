#include "MainMenuScene.h"
void MainMenuScene::LoadScene() {
	bse->RegisterEvent<SceneChangeEvent>();

	bse->SetBackgroundColor(glm::vec3(0.1f, 0.6f, 0.7f));

	SpawnTitle();
	SpawnButtons();
	SpawnInstructions();

	SetupInteraction();
}
void MainMenuScene::SpawnTitle() {
	title = new GameObject();

	Sprite* sprite = title->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/title.png", false);

	Transform* transform = title->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, 0.5, 0));
	transform->SetScale(glm::vec3(1.5, 0.5, 1));

	bse->AddGameObject(title);
}

void MainMenuScene::SpawnButtons() {
	
	startButton = new GameObject();

	Sprite* sprite = startButton->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/start.png", true);

	PhysicsBody* body = startButton->AddComponent<PhysicsBody>();
	body->SetOBB();

	Transform* transform = startButton->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, -0.05, 0));
	transform->SetScale(glm::vec3(1, 0.25, 1));

	bse->AddGameObject(startButton);

	howToPlayButton = new GameObject();
	sprite = howToPlayButton->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/howToPlay.png", true);

	body = howToPlayButton->AddComponent<PhysicsBody>();
	body->SetOBB();

	transform = howToPlayButton->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, -0.4, 0));
	transform->SetScale(glm::vec3(1, 0.25, 1));

	bse->AddGameObject(howToPlayButton);

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

	backButton = new GameObject();
	backButton->Disable();


	sprite = backButton->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/back.png", true);

	body = backButton->AddComponent<PhysicsBody>();
	body->SetOBB();

	transform = backButton->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, -0.75, 0));
	transform->SetScale(glm::vec3(1, 0.25, 1));

	bse->AddGameObject(backButton);
}

void MainMenuScene::SpawnInstructions() {
	instructions = new GameObject();

	instructions->Disable();

	Sprite* sprite = instructions->AddComponent<Sprite>();

	sprite->SetQuadGeometry();
	sprite->SetMaterial("./assets/instructions.png", true);

	Transform* transform = instructions->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, 0.2, 0));
	transform->SetScale(glm::vec3(1.75, 1.25, 1));

	bse->AddGameObject(instructions);
}

void MainMenuScene::SetupInteraction() {
	Input::AddTracking(1, GLFW_MOUSE_BUTTON_LEFT);
	Input::AddTracking(1, GLFW_KEY_ESCAPE);

	GameObject* holderOfTheScript = new GameObject();

	MainMenuController* mmc = holderOfTheScript->AddComponent<MainMenuController>();

	mmc->title = title;

	mmc->startButton = startButton;
	mmc->howToPlayButton = howToPlayButton;
	mmc->quitButton = quitButton;
	mmc->backButton = backButton;
	mmc->instructions = instructions;

	

	bse->AddGameObject(holderOfTheScript);

}
