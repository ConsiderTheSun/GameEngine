#include "Contact.h"


Contact::~Contact() {
	delete(collisionList);
	delete(collisionListLast);
}

void Contact::AddCollision(PhysicsBody* a, PhysicsBody* b, glm::vec3 n, float d) {
	CollisionData cd = {
		cd.normal = n,
		cd.depth = d
	};
	collisionList->insert(std::make_pair(std::make_pair(a,b ), cd));
}

void Contact::Reset() { 
	CollisionList* collisionListTemp;

	// clears collisions from last frame
	collisionListLast->clear();

	// swaps the collision lists
	collisionListTemp = collisionListLast;

	collisionListLast = collisionList;
	collisionList = collisionListTemp;

}

PhysicsBody* Contact::GetCollision(PhysicsBody* body) {
	if (body == NULL) return NULL;

	for (auto c : *collisionList) {
		if (c.first.first == body) {
			return c.first.second;
		}
		if (c.first.second == body) {
			return c.first.first;
		}
	}
	return NULL;
}

std::vector<PhysicsBody*> Contact::GetAllCollisions(PhysicsBody* body) {
	std::vector<PhysicsBody*> collisionVector;

	if (body == NULL) return collisionVector;
	
	for (auto c : *collisionList) {
		if (c.first.first == body) {
			collisionVector.push_back(c.first.second);
		}
		else if (c.first.second == body) {
			collisionVector.push_back(c.first.first);
		}
	}

	return collisionVector;
}


void Contact::RemoveGameObject(GameObject* gameObject) {
	bool found = false;
	do{
		found = false;
		for (const CollisionInstance& c : *collisionList) {
			if (c.first.first->gameObject == gameObject) {
				collisionList->erase(c.first);
			}
			else if (c.first.second->gameObject == gameObject) {
				collisionList->erase(c.first);
				found = true;
				break;
			}
		}
	} while (found);
}
