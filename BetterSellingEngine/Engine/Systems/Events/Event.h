#pragma once
#include <string>
#include <typeinfo>

#include <glm/glm/vec3.hpp>

class GameObject;
class Event {
public:
	std::string typeName;
	Event(GameObject* go) : eventObject(go) { typeName = typeid(*this).name(); }
	GameObject* eventObject = nullptr;
	virtual std::string GetType() { return typeName;}
};

class DestroyEvent : public Event {
public:
	DestroyEvent(GameObject* go) : Event(go) {
		typeName = typeid(*this).name();
	}
};

class CollisionEvent : public Event {
public:

	CollisionEvent(GameObject* go, GameObject* cObj, glm::vec3 n, float d) : Event(go) {
		collisionObject = cObj;
		typeName = typeid(*this).name();
		normal = n;
		depth = d;
	}

	GameObject* collisionObject = nullptr;

	glm::vec3 normal = glm::vec3();
	float depth = 0;
};
class CollisionEnterEvent : public CollisionEvent {
public:
	CollisionEnterEvent(GameObject* go, GameObject* cObj, glm::vec3 n, float d) : CollisionEvent(go, cObj, n, d) {
		typeName = typeid(*this).name();
	}
};

class CollisionExitEvent : public CollisionEvent {
public:
	CollisionExitEvent(GameObject* go, GameObject* cObj, glm::vec3 n, float d) : CollisionEvent(go, cObj, n, d) {
		typeName = typeid(*this).name();
	}
};