#include "GameScene.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
void GameScene::LoadScene() {

	Camera::GetInstance()->SetDimentions(Camera::Dimensions::Three);

	
	LetThereBeLight();

	bse->SetBackgroundColor(glm::vec3(0.1f, 0.6f, 0.7f));

	bse->RegisterEvent<SceneChangeEvent>();
	bse->RegisterEvent<CollisionEnterEvent>();
	bse->RegisterEvent<CollisionEvent>();
	bse->RegisterEvent<CollisionExitEvent>();
	bse->RegisterEvent<DestroyEvent>();

	Physics::GetInstance()->SetGravity(5);
	
	LayerSetup();

	CreateEnvironment();

	SpheresLikeThese();

	CreatePlayer();

	GameControllerSetup();

	CameraSetup(playerGO->GetChild(0));

	InputSetup();
}

void GameScene::LetThereBeLight() {
	bse->EnableLighting();

	bse->SetLightPosition(glm::vec3(0, 5, 0));
}


void GameScene::LayerSetup() {
	bse->RegisterLayer("Player Layer");
	bse->RegisterLayer("Ground Layer");
	bse->RegisterLayer("Projectile Layer");
	bse->RegisterLayer("Enemy Layer");
	bse->RegisterLayer("Victory Layer");

	bse->SetCollisionInteraction("default", "Player Layer", false);
	bse->SetCollisionInteraction("default", "Ground Layer", false);
	bse->SetCollisionInteraction("default", "Projectile Layer", false);
	bse->SetCollisionInteraction("default", "Enemy Layer", false);
	bse->SetCollisionInteraction("default", "Victory Layer", false);

	bse->SetCollisionInteraction("Player Layer", "Player Layer", false);
	bse->SetCollisionInteraction("Player Layer", "Ground Layer", true);
	bse->SetCollisionInteraction("Player Layer", "Projectile Layer", false);
	bse->SetCollisionInteraction("Player Layer", "Enemy Layer", true);
	bse->SetCollisionInteraction("Player Layer", "Victory Layer", true);

	bse->SetCollisionInteraction("Ground Layer", "Ground Layer", false);
	bse->SetCollisionInteraction("Ground Layer", "Projectile Layer", true);
	bse->SetCollisionInteraction("Ground Layer", "Enemy Layer", false);
	bse->SetCollisionInteraction("Ground Layer", "Victory Layer", false);

	bse->SetCollisionInteraction("Projectile Layer", "Projectile Layer", true);
	bse->SetCollisionInteraction("Projectile Layer", "Enemy Layer", true);
	bse->SetCollisionInteraction("Projectile Layer", "Victory Layer", false);

	bse->SetCollisionInteraction("Enemy Layer", "Enemy Layer", true);
	bse->SetCollisionInteraction("Enemy Layer", "Victory Layer", false);

}

void GameScene::SpawnPlatform(glm::vec3 position, float scale, glm::vec3 color) {
	GameObject* groundFriend = new GameObject("Platform");
	groundFriend->SetLayer("Ground Layer");

	groundFriend->AddComponent<Sprite>();

	Sprite* groundSprite = groundFriend->GetComponent<Sprite>();
	groundSprite->SetCylinderGeometry();
	groundSprite->SetColor(color);

	Transform* groundT = groundFriend->GetComponent<Transform>();
	float thicccness = 0.3;
	groundT->SetPosition(position - glm::vec3(0, thicccness, 0));
	groundT->SetRotation(glm::vec3(-M_PI / 2, 0, 0));
	groundT->SetScale(glm::vec3(scale, scale, thicccness));

	PhysicsBody* groundBody = groundFriend->AddComponent<PhysicsBody>();
	groundBody->SetCylinderAA();
	groundBody->SetHasGravity(false);

	bse->AddGameObject(groundFriend);

	platformManager->AddPlatform(groundFriend);
}

void GameScene::CreateEnvironment() {
	GameObject* platformManagerGO = new GameObject("Platform Manager");
	platformManager = platformManagerGO->AddComponent<PlatformManager>();
	
	bse->AddGameObject(platformManagerGO);

	EnemyManager::SetPlatformManager(platformManager);

	SpawnPlatform(glm::vec3(0, -0.5, 0), 20);

	SpawnPlatform(glm::vec3(21, -0.5, 0), 20);

	SpawnPlatform(glm::vec3(0, 0.0, 15), 20);

	
}

void GameScene::MakeASphere(glm::vec3 position, float scale, glm::vec3 color) {
	GameObject* sphereIsGoodFood = new GameObject("Platform");
	sphereIsGoodFood->SetLayer("Victory Layer");

	sphereIsGoodFood->AddComponent<Sprite>();

	Sprite* sphereSprite = sphereIsGoodFood->GetComponent<Sprite>();
	sphereSprite->SetSphereGeometry();
	sphereSprite->SetColor(color);

	Transform* sphereT = sphereIsGoodFood->GetComponent<Transform>();
	sphereT->SetPosition(position);
	sphereT->SetScale(glm::vec3(scale, scale, scale));

	PhysicsBody* sphereBody = sphereIsGoodFood->AddComponent<PhysicsBody>();
	sphereBody->SetSphere();
	sphereBody->SetHasGravity(false);

	bse->AddGameObject(sphereIsGoodFood);
}
void GameScene::SpheresLikeThese() {
	MakeASphere(glm::vec3(0, 1, 15), 1);
	MakeASphere(glm::vec3(0, 1, 10), 1);
}


void GameScene::CreatePlayer() {
	glm::vec3 playerColor = glm::vec3(0.5, 1, 0.6);
	playerGO = EntityFactory::MakeI("Player", "Player Layer", glm::vec3(1, 0, 0), playerColor);
	PlayerController* pc = playerGO->AddComponent<PlayerController>();
	pc->playerColor = playerColor;
	pc->victoryRequirement = 2;

	playerGO->GetComponent<PhysicsBody>()->SetHasGravity(true);
	playerGO->GetComponent<PhysicsBody>()->SetMass(pc->MASS);

	EnemyManager::SetPlayerGameObject(playerGO);
}

void GameScene::GameControllerSetup() {
	GameObject* scriptyGO = new GameObject("Script Container");
	scriptyGO->AddComponent<GameController>();
	scriptyGO->AddComponent<EnemyManager>();
	bse->AddGameObject(scriptyGO);

	/*GameObject* enemyManager = new GameObject("Enemy Manager");
	bse->AddGameObject(enemyManager);*/
}


void GameScene::CameraSetup(GameObject* followGO) {
	std::pair<unsigned int, unsigned int> ar = bse->GetWindow()->GetAspectRatio();
	Camera::MainCamera()->transform.SetScale(glm::vec3(1 * ar.first, 1 * ar.second, 1));


	GameObject* camControllerGO = new GameObject("Camera Controller");
	CameraController* cc = camControllerGO->AddComponent<CameraController>();

	cc->SetFollowObject(followGO);
	bse->AddGameObject(camControllerGO);
}

void GameScene::InputSetup() {

	Input::LockMouse();

	// player movement
	Input::AddTracking(5, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
		GLFW_KEY_D, GLFW_KEY_SPACE);

	// game controls
	Input::AddTracking(1, GLFW_KEY_ESCAPE);

	Input::AddTracking(2, GLFW_MOUSE_BUTTON_LEFT, GLFW_MOUSE_BUTTON_RIGHT);
}