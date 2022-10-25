#pragma once
#include <string>
#include <iostream>
#include "../Systems/Events/Event.h"
class GameObject;

class Component {

public:
	Component(GameObject* go) : gameObject(go) {}
	GameObject* gameObject;
	virtual std::string GetType() { return "Default Component"; };

	virtual void HandleEvent(Event* e) {};
};