#include "2dTesting.h"

void TwoDTesting::Setup() {
	bse = BetterSellingEngine::GetInstance();

	bse->Initialize("Hi, How are you?", Camera::Dimensions::Two);
	GameWindow* helloWindow = bse->GetWindow();

	helloWindow->SetAspectRatio(1, 1);
	helloWindow->SetMinWindowWidth(1000);

	bse->RegisterEvent<CollisionEvent>();
	bse->RegisterEvent<CollisionExitEvent>();
	bse->RegisterEvent<CollisionEnterEvent>();
	bse->RegisterEvent<DestroyEvent>();

	bse->RegisterLayer("Sad Layer");
	bse->RegisterLayer("Segy Layer");
	bse->RegisterLayer("What Layer");
	bse->SetCollisionInteraction("Sad Layer", "default", false);
	bse->SetCollisionInteraction("Sad Layer", "Segy Layer", true);
	bse->SetCollisionInteraction("Sad Layer", "What Layer", false);

	// empty boy, for scripty things
	GameObject* basicBoy = new GameObject("Won'tBeBasic");
	basicBoy->AddComponent<PlayerController2D>()->dimentions = Camera::Dimensions::Two;

	bse->AddGameObject(basicBoy);



	SpawnEntities();



	// camera fun
	std::pair<unsigned int, unsigned int> ar = helloWindow->GetAspectRatio();
	Camera::MainCamera()->transform.SetScale(glm::vec3(1 * ar.first, 1 * ar.second, 1));

	// buttons that do things

	// player movement
	Input::AddTracking(4, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S,
		GLFW_KEY_D);

	// object switching
	Input::AddTracking(2, GLFW_KEY_LEFT_BRACKET, GLFW_KEY_RIGHT_BRACKET);

	// gravity
	Input::AddTracking(3, GLFW_KEY_MINUS, GLFW_KEY_0, GLFW_KEY_1);

	// scale, rotation
	Input::AddTracking(5, GLFW_KEY_ESCAPE, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_LEFT, GLFW_KEY_RIGHT);

	// enable/disable collision between layers
	Input::AddTracking(2, GLFW_KEY_LEFT_SHIFT, GLFW_KEY_RIGHT_SHIFT);
}

void TwoDTesting::Start() {
	bse->Start();
	delete(bse);
}


void TwoDTesting::OneSegy(glm::vec3 position, float mass) {
	GameObject* segyGO = new GameObject("Segy");
	std::cout << "Spawning " << segyGO->GetName() << std::endl;
	segyGO->SetLayer("Segy Layer");

	segyGO->AddComponent<Sprite>();

	Sprite* segySprite = segyGO->GetComponent<Sprite>();
	segySprite->SetQuadGeometry();
	segySprite->SetColor(glm::vec3(1, 1, 1));
	segySprite->SetMaterial("./assets/segy.png");

	Transform* segyT = segyGO->GetComponent<Transform>();
	segyT->SetPosition(position);
	segyT->SetScale(glm::vec3(0.75f, 0.75f, 1));

	segyGO->AddComponent<PhysicsBody>();
	PhysicsBody* segyB = segyGO->GetComponent<PhysicsBody>();
	segyB->SetOBB();
	segyB->SetMass(mass);
	bse->AddGameObject(segyGO);
}
void TwoDTesting::SegyFriends() {
	OneSegy(glm::vec3(1.6f, 0.0f, 0));
	OneSegy(glm::vec3(2.6f, 1.0f, 0), 0.5f);
	OneSegy(glm::vec3(1.8f, 1.0f, 0), 0.5f);
	OneSegy(glm::vec3(0.6f, 1.0f, 0), 0.5f);
	OneSegy(glm::vec3(2.0f, 2.0f, 0), 0.5f);
	OneSegy(glm::vec3(1.6f, 1.0f, 0), 0.5f);
	OneSegy(glm::vec3(1, 0, 0), 0.5f);


	return;
	GameObject* segyGO2 = new GameObject("Segy2");
	std::cout << "Spawning " << segyGO2->GetName() << std::endl;

	segyGO2->SetLayer("Segy Layer");

	segyGO2->AddComponent<Sprite>();

	Sprite* segySprite2 = segyGO2->GetComponent<Sprite>();
	segySprite2->SetQuadGeometry();
	segySprite2->SetColor(glm::vec3(1, 1, 1));
	segySprite2->SetMaterial("./assets/segy.png");

	Transform* segyT2 = segyGO2->GetComponent<Transform>();
	segyT2->SetPosition(glm::vec3(2.6f, 1.0f, 0));
	segyT2->SetScale(glm::vec3(0.75f, 0.75f, 1));

	segyGO2->AddComponent<PhysicsBody>();
	PhysicsBody* segyB2 = segyGO2->GetComponent<PhysicsBody>();
	segyB2->SetOBB();
	segyB2->SetMass(0.5f);

	bse->AddGameObject(segyGO2);
}

void TwoDTesting::GlitchyFriends() {
	GameObject* segyGO = new GameObject("What");
	std::cout << "Spawning " << segyGO->GetName() << std::endl;
	segyGO->SetLayer("What Layer");

	segyGO->AddComponent<Sprite>();

	Sprite* segySprite = segyGO->GetComponent<Sprite>();
	segySprite->SetQuadGeometry();
	segySprite->SetColor(glm::vec3(1, 1, 1));
	segySprite->SetMaterial("./assets/what.png");

	Transform* segyT = segyGO->GetComponent<Transform>();
	segyT->SetPosition(glm::vec3(0.0f, 0.5f, 0));
	segyT->SetScale(glm::vec3(0.75f, 0.75f, 1));

	segyGO->AddComponent<PhysicsBody>();
	PhysicsBody* segyB = segyGO->GetComponent<PhysicsBody>();
	segyB->SetOBB();

	bse->AddGameObject(segyGO);
}

void TwoDTesting::GarfTris() {
	// first oby
	GameObject* helloGameObject = new GameObject("How, Hi are you?");
	std::cout << "Spawning " << helloGameObject->GetName() << std::endl;

	helloGameObject->AddComponent<Sprite>();
	Sprite* helloSprite = helloGameObject->GetComponent<Sprite>();
	helloSprite->SetTriangleGeometry();
	helloSprite->SetColor(glm::vec3(1, 1, 1));
	helloSprite->SetMaterial("./assets/tiwy.png");

	helloSprite->SetCustomShader("Applications/2dTesting/custom.vert", "Applications/2dTesting/custom.frag");


	Transform* helloTransform = helloGameObject->GetComponent<Transform>();
	helloTransform->SetPosition(glm::vec3(0.0f, 0.0f, -1));
	helloTransform->SetRotation(glm::vec3(0.0f, 0.0f, 0));
	helloTransform->SetScale(glm::vec3(1, 0.5f, 1));


	bse->AddGameObject(helloGameObject);
	// first child
	GameObject* hiGO = new GameObject("Hi");
	std::cout << "Spawning " << hiGO->GetName() << std::endl;
	hiGO->AddComponent<Sprite>();

	Sprite* hiSprite = hiGO->GetComponent<Sprite>();
	hiSprite->SetTriangleGeometry();
	hiSprite->SetColor(glm::vec3(0.8f, 1, 0.8f));
	hiSprite->SetMaterial("./assets/tiwy.png");

	Transform* hiT = hiGO->GetComponent<Transform>();
	hiT->SetPosition(glm::vec3(0.5f, 0.0f, 0));

	bse->AddGameObject(hiGO, helloGameObject);

	// second child
	GameObject* hiGO2 = new GameObject("Hi2");
	std::cout << "Spawning " << hiGO2->GetName() << std::endl;
	hiGO2->AddComponent<Sprite>();

	hiSprite = hiGO2->GetComponent<Sprite>();
	hiSprite->SetTriangleGeometry();
	hiSprite->SetColor(glm::vec3(0.8f, 1, 0.8f));
	hiSprite->SetMaterial("./assets/tiwy.png");

	hiT = hiGO2->GetComponent<Transform>();
	hiT->SetPosition(glm::vec3(-0.5f, 0.0f, 0));

	bse->AddGameObject(hiGO2, helloGameObject);

	// third child
	GameObject* hiGO3 = new GameObject("Hi3");
	std::cout << "Spawning " << hiGO3->GetName() << std::endl;
	hiGO3->AddComponent<Sprite>();

	hiSprite = hiGO3->GetComponent<Sprite>();
	hiSprite->SetTriangleGeometry();
	hiSprite->SetColor(glm::vec3(0.8f, 1, 0.8f));
	hiSprite->SetMaterial("./assets/tiwy.png");

	hiT = hiGO3->GetComponent<Transform>();
	hiT->SetPosition(glm::vec3(0.5f, -1.0f, 0));

	bse->AddGameObject(hiGO3, hiGO);

	// fourth child
	GameObject* hiGO4 = new GameObject("Hi4");
	std::cout << "Spawning " << hiGO4->GetName() << std::endl;
	hiGO4->AddComponent<Sprite>();

	hiSprite = hiGO4->GetComponent<Sprite>();
	hiSprite->SetTriangleGeometry();
	hiSprite->SetColor(glm::vec3(0.8f, 1, 0.8f));
	hiSprite->SetMaterial("./assets/tiwy.png");

	hiT = hiGO4->GetComponent<Transform>();
	hiT->SetPosition(glm::vec3(-0.5f, -1.0f, 0));

	bse->AddGameObject(hiGO4, hiGO);

	// fifth child
	GameObject* hiGO5 = new GameObject("Hi5");
	std::cout << "Spawning " << hiGO5->GetName() << std::endl;
	hiGO5->AddComponent<Sprite>();

	hiSprite = hiGO5->GetComponent<Sprite>();
	hiSprite->SetTriangleGeometry();
	hiSprite->SetColor(glm::vec3(0.8f, 1, 0.8f));
	hiSprite->SetMaterial("./assets/tiwy.png");

	hiT = hiGO5->GetComponent<Transform>();
	hiT->SetPosition(glm::vec3(-0.5f, -1.0f, 0));

	bse->AddGameObject(hiGO5, hiGO2);


	//bse->RemoveGameObject(hiGO2);
	//hiGO5->SetParent();
}

void TwoDTesting::CircleBuddy() {
	GameObject* lemonGO = new GameObject("LemonOfPink");
	std::cout << "Spawning " << lemonGO->GetName() << std::endl;

	lemonGO->SetLayer("What Layer");

	lemonGO->AddComponent<Sprite>();

	Sprite* lemonSprite = lemonGO->GetComponent<Sprite>();
	lemonSprite->SetCircleGeometry(40);
	lemonSprite->SetColor(glm::vec3(1, 1, 1));
	lemonSprite->SetMaterial("./assets/lemonOfPink.png");

	Transform* lemonT = lemonGO->GetComponent<Transform>();
	lemonT->SetPosition(glm::vec3(1, 1.75, 0));
	lemonT->SetScale(glm::vec3(0.5, 0.5, 1));

	lemonGO->AddComponent<PhysicsBody>();
	PhysicsBody* lemonB = lemonGO->GetComponent<PhysicsBody>();
	lemonB->SetCircle();

	bse->AddGameObject(lemonGO);
}
void TwoDTesting::SpawnEntities() {
	// random solid color triangle, just to show I can
	GameObject* boringSolid = new GameObject("solid");
	std::cout << "Spawning " << boringSolid->GetName() << std::endl;
	boringSolid->AddComponent<Sprite>();

	Sprite* boringSprite = boringSolid->GetComponent<Sprite>();
	boringSprite->SetTriangleGeometry();
	boringSprite->SetColor(glm::vec3(0.5, 1, 0.5));

	Transform* boringT = boringSolid->GetComponent<Transform>();

	boringT->SetPosition(glm::vec3(0.0f, 5.0f, 0));
	boringT->SetScale(glm::vec3(2, 2, 1));
	bse->AddGameObject(boringSolid);

	
	GarfTris();
	
	SegyFriends();
	GlitchyFriends();
	
	CircleBuddy();
	// sad

	GameObject* sadGO = new GameObject("Sad");
	std::cout << "Spawning " << sadGO->GetName() << std::endl;

	sadGO->SetLayer("Sad Layer");
	std::cout << "Sad Layer: " << sadGO->GetLayer() << std::endl;

	sadGO->AddComponent<Sprite>();

	Sprite* sadSprite = sadGO->GetComponent<Sprite>();
	sadSprite->SetQuadGeometry();
	sadSprite->SetColor(glm::vec3(1, 1, 1));
	sadSprite->SetMaterial("./assets/sad.png");

	Transform* sadT = sadGO->GetComponent<Transform>();

	sadT->SetPosition(glm::vec3(1.0f, 1.0f, 0));
	sadT->SetScale(glm::vec3(0.5f, 0.5f, 1));


	sadGO->AddComponent<PhysicsBody>();
	PhysicsBody* sadB = sadGO->GetComponent<PhysicsBody>();
	sadB->SetOBB();

	sadGO->AddComponent<WhenSadCollides2D>();
	//sadGO->AddComponent<PhysicsPlay>();
	bse->AddGameObject(sadGO);

	
}