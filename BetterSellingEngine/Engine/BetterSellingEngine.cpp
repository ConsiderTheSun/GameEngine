#include "BetterSellingEngine.h"

void BetterSellingEngine::Initialize(std::string windowName, Camera::Dimensions d) {

	previousFrame = std::chrono::steady_clock::now();

	gameWindow.Init(windowName);

	gomSystem = GOM::GetInstance();

	Input::Init(&gameWindow);

	mainCamera = Camera::GetInstance(d);

	renderSystem.Init();

	physicsSystem = Physics::GetInstance();

	eventManagerSystem = EventManager::GetInstance();
}

void BetterSellingEngine::LoadFromFile(std::string fileName) {
	GameObjectFactory::CreateAllGameObjects(this, fileName);
}

void BetterSellingEngine::Start() {
	if (currentScene) {
		currentScene->LoadScene();
	}

	while (!gameWindow.ShouldClose()) {
		
		deltaTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - previousFrame).count();
		previousFrame = std::chrono::steady_clock::now();

		float remainingTime = deltaTime;
		int loops = 0;
		float minDelta = 1.0f / 60;
		while (remainingTime > 0) {
			
			FixedUpdate(std::min(remainingTime, minDelta));
			remainingTime -= 1.0f / 60;

			++loops;

			if (loops > 10) {
				//std::cout << "PROBLEMS PROBLEMS PROBLEMS\n";
				break;
			}
		}

		// I couldn't get this working due to time constraints, good luck Kelsey
		//FixedUpdate(deltaTime);
		
		Update(deltaTime);

		gameWindow.SwapBuffer();

		glfwPollEvents();
	}

	Shutdown();
}

void BetterSellingEngine::Update(float dt) {

	
	mainCamera->Update();

	Input::Update(); 


	ScriptManagerSystem.Update(gomSystem, dt);

	eventManagerSystem->HandleEvents();

	HandleDestroyEvents(eventManagerSystem->GetDestroyEvents()); 

	renderSystem.Draw(mainCamera, gomSystem); 

	HandleSceneChangeEvent(eventManagerSystem->GetSceneChangeEvent()); 
}

void BetterSellingEngine::FixedUpdate(float dt) {
	physicsSystem->Update(gomSystem, dt);
}
void BetterSellingEngine::HandleDestroyEvents(std::vector<DestroyEvent*>& eList) {
	while (eList.size() != 0) {
		for (int i = 0; i < eList.size(); ++i) {
			bool hasChildInList = false;
			for (int j = i + 1; j < eList.size(); ++j) {
				if (gomSystem->HasChild(eList[i]->eventObject, eList[j]->eventObject)) {
					hasChildInList = true;
				}

				if (eList[i]->eventObject == eList[j]->eventObject) {
					eList.erase(eList.begin() + j);
					j--;
				}
			}

			if (!hasChildInList) {
				RemoveGameObject(eList[i]->eventObject);
				eList.erase(eList.begin() + i);
				i--;
			}
		}
	}
}

void BetterSellingEngine::AddGameObject(GameObject* gameObject, GameObject* parent) {
	gomSystem->AddGameObject(gameObject, parent);
}
void BetterSellingEngine::RemoveGameObject(GameObject* gameObject) {
	physicsSystem->RemoveGameObject(gameObject);
	gomSystem->RemoveGameObject(gameObject);
}

void BetterSellingEngine::RegisterLayer(std::string newLayerName) {
	bool success = gomSystem->AddLayer(newLayerName);
	if (success) {
		physicsSystem->ExpandCollisionTable(gomSystem->layerCount);
	}
}
bool BetterSellingEngine::GetCollisionInteraction(std::string layer1, std::string layer2) {
	return physicsSystem->LayerInteraction(gomSystem->LayerToInt(layer1), gomSystem->LayerToInt(layer2));
}
void BetterSellingEngine::SetCollisionInteraction(std::string layer1, std::string layer2, bool interaction) {
	physicsSystem->SetCollisionInteraction(gomSystem->LayerToInt(layer1), gomSystem->LayerToInt(layer2), interaction);
}


BetterSellingEngine* BetterSellingEngine::engineInstance = nullptr;
BetterSellingEngine* BetterSellingEngine::GetInstance() {
	if (!engineInstance)
		engineInstance = new BetterSellingEngine();
	return engineInstance;
};


void BetterSellingEngine::Shutdown() {
	glfwTerminate();
}

BetterSellingEngine::~BetterSellingEngine() {
	engineInstance = nullptr;
	delete(mainCamera);
	delete(gomSystem);
	delete(physicsSystem);
	delete(eventManagerSystem);
}



void BetterSellingEngine::ChangeScene(Scene* initScene) {
	SceneChangeEvent* e = new SceneChangeEvent(initScene);
	EventManager::GetInstance()->AddEvent(e);

}

void BetterSellingEngine::HandleSceneChangeEvent(SceneChangeEvent* e) {
	if (!e) return;
	// clears the previous scene
	gomSystem->Reset();
	physicsSystem->Reset();
	renderSystem.Reset();
	eventManagerSystem->Reset();
	mainCamera->Reset();

	Input::Reset();


	if(currentScene) delete(currentScene);
	// loads the new scene
	currentScene = e->newScene;
	currentScene->LoadScene();

	delete(e);
}


void BetterSellingEngine::LoadNewScene(Scene* newScene) {
	UnloadScene();
	delete(currentScene);
	currentScene = newScene;
	currentScene->LoadScene();
}

void BetterSellingEngine::UnloadScene() {
	gomSystem->Clear();
}