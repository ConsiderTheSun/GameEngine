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

	void Update();

	void Shutdown();


	void HandleDestroyEvents(std::vector<DestroyEvent*>& eList);

};
