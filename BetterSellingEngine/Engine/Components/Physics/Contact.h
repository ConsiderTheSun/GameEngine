#pragma once
#include <set>
#include <map>

#include "PhysicsBody.h"
#include "../../GameObject.h"

#include <iostream>





struct CollisionData {
	glm::vec3 normal = glm::vec3();
	float depth = 0;
};

typedef std::map<std::pair<PhysicsBody*, PhysicsBody*>, CollisionData> CollisionList;
typedef std::pair<std::pair<PhysicsBody*, PhysicsBody*>, CollisionData> CollisionInstance;
class Contact {
public:
	~Contact();

	void AddCollision(PhysicsBody* a, PhysicsBody* b, glm::vec3 n, float d);
	void Reset();
	void Print() {
		std::cout << "Collisions:\n";
		for (auto c : *collisionList) {
			std::cout << "[" << c.first.first->gameObject->GetName() << ", "
				<< c.first.second->gameObject->GetName() << "]\n";
		}
		std::cout << "\n\n";
	};

	PhysicsBody* GetCollision(PhysicsBody* body1);
	std::vector<PhysicsBody*> GetAllCollisions(PhysicsBody* body1);

	const CollisionList* GetCollisionList() {
		return collisionList;
	}

	const CollisionList* GetCollisionListLast() {
		return collisionListLast;
	}
private:
	CollisionList* collisionList =
		new CollisionList();
	CollisionList* collisionListLast =
		new CollisionList();

	void RemoveGameObject(GameObject* gameObject);

	friend class Physics;
};