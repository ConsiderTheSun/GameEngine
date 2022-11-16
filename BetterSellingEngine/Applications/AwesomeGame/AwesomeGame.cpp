

#include "AwesomeGame.h"

void AwesomeGame::Setup() {
	bse = BetterSellingEngine::GetInstance();
	bse->Initialize("This is a game", Camera::Dimensions::Three);
	
	CreateWindow();

	//bse->RegisterEvent<CollisionEvent>();
	bse->RegisterEvent<CollisionExitEvent>();
	bse->RegisterEvent<CollisionEnterEvent>();
	bse->RegisterEvent<DestroyEvent>();

	CreateEnvironment();

	GameObject* playerGO = CreatePlayer();

	GameControllerSetup();

	CameraSetup(playerGO);
	InputSetup();
}

void AwesomeGame::CreateWindow() {
	GameWindow* awesomeWindow = bse->GetWindow();

	awesomeWindow->SetAspectRatio(1, 1);
	awesomeWindow->SetMinWindowWidth(1000);
}

GameObject* AwesomeGame::CreatePlayer() {
	GameObject* playerGO = EntityFactory::MakeI("Player", glm::vec3(1,0,0), glm::vec3(0.5, 1, 0.6));
	playerGO->AddComponent<PlayerController>();

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//TODO: remove this (useful testing sphere)
	///////////////////////////////////////////////////////////////////////////////////////////////////
	GameObject* tempSphereGO = new GameObject("Temp");
	tempSphereGO->AddComponent<Sprite>();

	Sprite* spritey = tempSphereGO->GetComponent<Sprite>();
	spritey->SetSphereGeometry();
	spritey->SetColor(glm::vec3(0.5, 0.5, 0.5));

	Transform* transformy = tempSphereGO->GetComponent<Transform>();

	transformy->SetPosition(glm::vec3(5, 0, 0));
	transformy->SetScale(glm::vec3(0.2, 0.2, 0.2));

	tempSphereGO->AddComponent<PhysicsBody>()->SetSphere();
	bse->AddGameObject(tempSphereGO);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////

	return playerGO;
}


void AwesomeGame::CreateEnvironment() {
	GameObject* groundFriend = new GameObject("Ground");
	groundFriend->AddComponent<Sprite>();

	Sprite* groundSprite = groundFriend->GetComponent<Sprite>();
	groundSprite->SetQuadGeometry();
	groundSprite->SetColor(glm::vec3(0, 0.5, 0.07));

	Transform* groundT = groundFriend->GetComponent<Transform>();

	groundT->SetPosition(glm::vec3(0, -0.5, 0));
	groundT->SetRotation(glm::vec3(-3.14 / 2, 0, 0));
	groundT->SetScale(glm::vec3(20, 20, 1));


	bse->AddGameObject(groundFriend);
}

void AwesomeGame::GameControllerSetup() {
	GameObject* scriptyGO = new GameObject("Script Container");
	scriptyGO->AddComponent<GameController>();
	scriptyGO->AddComponent<EnemyManager>();
	bse->AddGameObject(scriptyGO);

	/*GameObject* enemyManager = new GameObject("Enemy Manager");
	bse->AddGameObject(enemyManager);*/
}


void AwesomeGame::CameraSetup(GameObject* followGO) {
	std::pair<unsigned int, unsigned int> ar = bse->GetWindow()->GetAspectRatio();
	Camera::MainCamera()->transform.SetScale(glm::vec3(1 * ar.first, 1 * ar.second, 1));


	GameObject* camControllerGO = new GameObject("Camera Controller");
	CameraController* cc = camControllerGO->AddComponent<CameraController>();

	cc->SetFollowObject(followGO);
	bse->AddGameObject(camControllerGO);
}

void AwesomeGame::InputSetup() {

	Input::LockMouse();

	// player movement
	Input::AddTracking(4, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
		GLFW_KEY_D);

	// game controls
	Input::AddTracking(1, GLFW_KEY_ESCAPE);

	Input::AddTracking(1, GLFW_MOUSE_BUTTON_RIGHT);
}

void AwesomeGame::Start() {

	bse->Start();
	delete(bse);
}

