#pragma once

#include <iostream>
#include <vector>
#include <type_traits>
#include <typeinfo>
#include <typeindex>
#include <list>

#include <glm/glm/vec3.hpp>

#include "Components/Component.h"
#include "Components/Sprite/Sprite.h"
#include "Components/Transform.h"
#include "Systems/Events/Event.h"
#include "Systems/Events/EventManager.h"
class GameObject{

public:
	Transform* transform;

	GameObject(std::string name="GameObject", glm::vec3 position=glm::vec3(0,0,0));
	~GameObject();

	const std::string& GetName() { return name; }

	GameObject* GetParent() { return parent; }
	GameObject* GetChild(int index);
	const std::list<GameObject*>& getChildrenList() const { return children; }

	bool SetParent(GameObject* parent = NULL);

	std::string GetLayerName();
	int GetLayer();
	void SetLayer(std::string layerName);

	void HandleEvent(Event* e);

	static void Destroy(GameObject* go);
	void Destroy();

	template <typename T,
		typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
	inline T* AddComponent();

	template <typename T,
		typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
	inline T* GetComponent();
	template <typename T,
		typename = std::enable_if_t<std::is_base_of_v<Component, T>>>
	inline std::vector<T*> GetAllComponents();

private:
	GameObject* parent = NULL;
	std::list<GameObject*> children;
	std::vector<Component*> componentList;
	
	std::string name;

	int layer = 0;
	
	void UpdateTransform();

	friend class GameObjectManager;
	friend class Transform;
};