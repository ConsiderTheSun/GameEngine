#pragma once
#include "Component.h"
#include "../GameObject.h"
#include "../Systems/Events/Event.h"
#include <iostream>
class Script : public Component {
public:
	Script(GameObject* go) : Component(go) {}

	virtual void Update(float dt) {}

	void HandleEvent(Event* e) override;

	virtual void OnCollisionEnter(CollisionEvent* e) {}
	virtual void OnCollision(CollisionEvent* e) {}
	virtual void OnCollisionExit(CollisionEvent* e) {}
};