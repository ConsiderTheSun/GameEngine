#pragma once

#include "engineIncludes.h"
#include "GameObjectFactory.h"
class BetterSellingEngine
{
public:

	void Initialize(std::string windowName = "Untitled", Camera::Dimensions d = Camera::Dimensions::Two);
	void Start();
	void End() { glfwSetWindowShouldClose(gameWindow.window, true); }
	
	void LoadFromFile(std::string fileName);

	~BetterSellingEngine();

	static BetterSellingEngine* GetInstance();
	GameWindow* GetWindow() { return &gameWindow; }
	void AddGameObject(GameObject* gameObject, GameObject* parent = NULL);
	void RemoveGameObject(GameObject* gameObject);

	void RegisterLayer(std::string newLayerName);
	bool GetCollisionInteraction(std::string layer1, std::string layer2);
	void SetCollisionInteraction(std::string layer1, std::string layer2, bool interaction);

	void AddEvent(Event* e);

	void EnableLighting() { renderSystem.EnableLighting(); }
	void DisableLighting() { renderSystem.DisableLighting(); }
	void SetLightPosition(glm::vec3 newPos) { renderSystem.SetLightPosition(newPos); }
	glm::vec3 GetLightPosition() { return renderSystem.GetLightPosition(); }

	void SetInitialScene(Scene* initScene) { currentScene = initScene; }
	void ChangeScene(Scene* initScene);
	
	void SetBackgroundColor(glm::vec3 color) { renderSystem.SetBackgroundColor(color); }

	template <typename T,
		typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
	inline void RegisterEvent() {
		eventManagerSystem->RegisterEvent<T>();
	}
	template <typename T,
		typename = std::enable_if_t<std::is_base_of_v<Event, T>>>
	inline void UnregisterEvent() {
		eventManagerSystem->UnregisterEvent<T>();
	}
	
private:
	static BetterSellingEngine* engineInstance;

	
	GameWindow gameWindow;

	Camera* mainCamera;
	Renderer renderSystem;
	GOM* gomSystem;
	ScriptManager ScriptManagerSystem;
	Physics* physicsSystem;
	EventManager* eventManagerSystem;

	std::chrono::steady_clock::time_point previousFrame;
	float deltaTime = 0;

	Scene* currentScene = nullptr;

	void Update(float dt);
	void FixedUpdate(float dt);

	void Shutdown();


	void HandleDestroyEvents(std::vector<DestroyEvent*>& eList);

	void HandleSceneChangeEvent(SceneChangeEvent* e);
	void LoadNewScene(Scene* newScene);
	void UnloadScene();
};
