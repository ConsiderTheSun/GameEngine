#pragma once

#include "GameObjectManager.h"
#include "../Components/Physics/PhysicsBody.h"
#include "../Components/Physics/CollisionTest.h"
#include "../Components/Physics/Contact.h"

#include "Events/EventManager.h"
#include "Events/Event.h"

typedef std::vector<std::vector<bool>> CollisionTable;

class Physics
{
public:

	static Physics* GetInstance();

	Physics();
	void SetGravity(float newG) { gravity = newG; }
	float GetGravity() { return gravity; }

	void Update(GOM* gom, float dt);

	void EvaluateCollisions(GOM* gom);

	void BroadcastCollisions();

	PhysicsBody* GetCollision(GameObject* go1);
	std::vector<PhysicsBody*> GetAllCollisions(GameObject* go1);

	void RemoveGameObject(GameObject* gameObject);

	void SetCollisionInteraction(int layer1, int layer2, bool interaction);
	bool LayerInteraction(int layer1, int layer2);

	void Reset();
private:
	static Physics* physicsInstance;

	EventManager* eventManager = EventManager::GetInstance();
	Contact contact;

	float gravity = 0;

	CollisionTable collisionTable;

	void ExpandCollisionTable(int newSize);

	friend class BetterSellingEngine;
};
