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
	while (!gameWindow.ShouldClose()) {
		
		

		Update();

		gameWindow.SwapBuffer();

		glfwPollEvents();
	}

	Shutdown();
}

void BetterSellingEngine::Update() {

	deltaTime = std::chrono::duration<float>(std::chrono::steady_clock::now() - previousFrame).count();
	previousFrame = std::chrono::steady_clock::now();

	mainCamera->Update();

	Input::Update();

	physicsSystem->Update(gomSystem);

	ScriptManagerSystem.Update(gomSystem, deltaTime);

	eventManagerSystem->HandleEvents();

	HandleDestroyEvents(eventManagerSystem->GetDestroyEvents());

	renderSystem.Draw(mainCamera, gomSystem);
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