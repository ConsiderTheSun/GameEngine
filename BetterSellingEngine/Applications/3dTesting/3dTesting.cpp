#include "3dTesting.h"

void ThreeDTesting::Setup() {
	bse = BetterSellingEngine::GetInstance();

	bse->Initialize("Hi, How are you?", Camera::Dimensions::Three);
	GameWindow* helloWindow = bse->GetWindow();

	helloWindow->SetAspectRatio(1, 1);
	helloWindow->SetMinWindowWidth(1000);

	bse->RegisterEvent<CollisionEvent>();
	bse->RegisterEvent<CollisionExitEvent>();
	bse->RegisterEvent<CollisionEnterEvent>();
	bse->RegisterEvent<DestroyEvent>();

	// empty boy, for scripty things
	GameObject* basicBoy = new GameObject("Won'tBeBasic");
	basicBoy->AddComponent<PlayerController3D>();
	basicBoy->AddComponent<SillyThings>();

	bse->AddGameObject(basicBoy);

	SpawnEntities();

	// camera fun
	std::pair<unsigned int, unsigned int> ar = helloWindow->GetAspectRatio();
	Camera::MainCamera()->transform.SetScale(glm::vec3(1 * ar.first, 1 * ar.second, 1));

	Input::LockMouse();


	// buttons that do things

	// player movement
	Input::AddTracking(6, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
		GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT);

	// object movement
	Input::AddTracking(6, GLFW_KEY_I, GLFW_KEY_J, GLFW_KEY_K,
		GLFW_KEY_L, GLFW_KEY_O, GLFW_KEY_P);

	// object switching
	Input::AddTracking(2, GLFW_KEY_LEFT_BRACKET, GLFW_KEY_RIGHT_BRACKET);

	// gravity
	Input::AddTracking(3, GLFW_KEY_MINUS, GLFW_KEY_0, GLFW_KEY_1);

	// 3d rotation
	Input::AddTracking(6, GLFW_KEY_T, GLFW_KEY_Y, GLFW_KEY_G,
		GLFW_KEY_H, GLFW_KEY_B, GLFW_KEY_N);

	// scale
	Input::AddTracking(3, GLFW_KEY_ESCAPE, GLFW_KEY_UP, GLFW_KEY_DOWN);

	// spawn cube
	Input::AddTracking(1, GLFW_MOUSE_BUTTON_LEFT);

	
}

void ThreeDTesting::Start() {
	bse->Start();
	delete(bse);
}
void ThreeDTesting::SpawnEntities() {
	
	ACircleBut3D();
	ThesePlainPlanes();

	SpawnGround();

	LikeStarsInTheSky();

	SpawnCylinderThing();

	GameObject* sadGO = SillyThings::SpawnSadFriend(glm::vec3());

	sadGO->AddComponent<WhenSadCollides3D>();
	sadGO->AddComponent<PhysicsPlay>();

	LetThereBeLight();
}

void ThreeDTesting::LetThereBeLight() {
	bse->EnableLighting();
	bse->SetLightPosition(glm::vec3(0, 3, 0));

	GameObject* sunGO = new GameObject("Black Hole Sun");

	//Sprite* sunSprite = sunGO->AddComponent<Sprite>();
	sunGO->AddComponent<Sprite>();

	Sprite* sunSprite = sunGO->GetComponent<Sprite>();
	sunSprite->SetCubeGeometry();
	sunSprite->SetColor(glm::vec3(1, 1, 1));
	sunSprite->SetMaterial("./assets/blackHole.png");



	Transform* sunT = sunGO->GetComponent<Transform>();
	sunT->SetPosition(glm::vec3(0, 3, 0));
	sunT->SetScale(glm::vec3(0.1, 0.1, 0.1));

	sunGO->AddComponent<SunController>();

	bse->AddGameObject(sunGO);

}

void ThreeDTesting::ThesePlainPlanes() {
	GameObject* planeFriend = new GameObject("PlainPlane");
	planeFriend->AddComponent<Sprite>();

	Sprite* pSprite = planeFriend->GetComponent<Sprite>();
	pSprite->SetQuadGeometry();
	pSprite->SetColor(glm::vec3(0, 0.5, 0.07));

	Transform* pT = planeFriend->GetComponent<Transform>();

	pT->SetPosition(glm::vec3(0, 0, 0));
	pT->SetRotation(glm::vec3(0, 3.14, 0));
	pT->SetScale(glm::vec3(1, 1, 1));


	bse->AddGameObject(planeFriend);
}

void ThreeDTesting::ACircleBut3D() {
	GameObject* sphereBud = new GameObject("Sphere==Best Friend");
	sphereBud->AddComponent<Sprite>();

	Sprite* sphereSprite = sphereBud->GetComponent<Sprite>();
	sphereSprite->SetSphereGeometry(100);
	sphereSprite->SetColor(glm::vec3(1, 0.8, 1));
	//sphereSprite->SetColor(glm::vec3(0, 0, 0));
	//sphereSprite->SetMaterial("./assets/47.png");

	Transform* sphereyT = sphereBud->GetComponent<Transform>();

	sphereyT->SetPosition(glm::vec3(2,2,2));

	bse->AddGameObject(sphereBud);
}
void ThreeDTesting::SpawnGround() {

	GameObject* groundFriend = new GameObject("Ground");
	groundFriend->AddComponent<Sprite>();

	Sprite* cubeySprite = groundFriend->GetComponent<Sprite>();
	cubeySprite->SetQuadGeometry();
	cubeySprite->SetColor(glm::vec3(0, 0.5, 0.07));

	Transform* cubeyT = groundFriend->GetComponent<Transform>();

	cubeyT->SetPosition(glm::vec3(0, -1, 0));
	cubeyT->SetRotation(glm::vec3(-3.14 / 2, 0, 0));
	cubeyT->SetScale(glm::vec3(10, 10, 1));
	groundFriend->AddComponent<PhysicsBody>();
	PhysicsBody* cubeB = groundFriend->GetComponent<PhysicsBody>();
	cubeB->SetOBB();
	cubeB->SetHasGravity(false);

	bse->AddGameObject(groundFriend);
}

void ThreeDTesting::SpawnFriendCube(glm::vec3 pos) {

	// cube maybe hopefully
	GameObject* cubeFriend = new GameObject("Cube==Friend");
	cubeFriend->AddComponent<Sprite>();

	Sprite* cubeySprite = cubeFriend->GetComponent<Sprite>();
	cubeySprite->SetCubeGeometry();
	cubeySprite->SetColor(glm::vec3(1, 1, 1));
	cubeySprite->SetMaterial("./assets/47.png");

	Transform* cubeyT = cubeFriend->GetComponent<Transform>();

	cubeyT->SetPosition(pos);

	cubeFriend->AddComponent<PhysicsBody>();
	PhysicsBody* cubeB = cubeFriend->GetComponent<PhysicsBody>();
	cubeB->SetOBC2AA();

	bse->AddGameObject(cubeFriend);
}

void ThreeDTesting::LikeStarsInTheSky() {
	SpawnFriendCube(glm::vec3(0, 2, -2));
	SpawnFriendCube(glm::vec3(2, 1, 0));

	return;
	for (int i = 0; i < 10; i++) {
		float randomX = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0f)) - 30;
		float randomZ = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 60.0f)) - 30;

		float randomY = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 10.0f)) + 10;

		SpawnFriendCube(glm::vec3(randomX, randomY, randomZ));
	}
}


void ThreeDTesting::SpawnCylinderThing() {
	GameObject* cylinderThing = new GameObject("Thing==Friend");
	cylinderThing->AddComponent<Sprite>();

	Sprite* thingSprite = cylinderThing->GetComponent<Sprite>();
	thingSprite->SetCylinderGeometry(30);
	thingSprite->SetColor(glm::vec3(0.5, 1, 0.6));
	//thingSprite->SetMaterial("./assets/47.png");

	PhysicsBody* body = cylinderThing->AddComponent<PhysicsBody>();
	body->SetCylinderAA();

	Transform* cylT = cylinderThing->GetComponent<Transform>();

	cylT->SetPosition(glm::vec3(3,3,0));

	

	bse->AddGameObject(cylinderThing);




	GameObject* cylinderThing2 = new GameObject("Thing==Friend 2.0");
	cylinderThing2->AddComponent<Sprite>();

	thingSprite = cylinderThing2->GetComponent<Sprite>();
	thingSprite->SetCylinderGeometry(30);
	thingSprite->SetColor(glm::vec3(1, 0.5, 0.6));
	//thingSprite->SetMaterial("./assets/47.png");

	body = cylinderThing2->AddComponent<PhysicsBody>();
	body->SetCylinderAA();

	cylinderThing2->AddComponent<CylinderTester>();

	cylT = cylinderThing2->GetComponent<Transform>();

	cylT->SetPosition(glm::vec3(3, 1, 0));



	bse->AddGameObject(cylinderThing2);
}