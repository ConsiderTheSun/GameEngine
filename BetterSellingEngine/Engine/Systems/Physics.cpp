#include "Physics.h"

Physics* Physics::physicsInstance = nullptr;
Physics* Physics::GetInstance() {
	if (!physicsInstance)
		physicsInstance = new Physics();
	return physicsInstance;
}

Physics::Physics() {
	collisionTable.push_back(std::vector<bool>(1, true));
}

void Physics::Update(GOM* gom) {
	for (GOM::Iterator gomItr = gom->begin(), end = gom->end(); gomItr != end; ++gomItr) {
		// gets the body and skips GOs that don't have one
		PhysicsBody* bodyComponent = gomItr->GetComponent<PhysicsBody>();
		if (!bodyComponent) continue;

		bodyComponent->Integrate(gravity);
	}

	
	contact.Reset(); 
	EvaluateCollisions(gom);
	BroadcastCollisions();	

}




void Physics::EvaluateCollisions(GOM* gom) {
	for (GOM::Iterator gomItr = gom->begin(), end = gom->end(); gomItr != end; ++gomItr) {
		// gets the body and skips GOs that don't have one
		PhysicsBody* bodyComponent = gomItr->GetComponent<PhysicsBody>();
		if (!bodyComponent) continue;

		GOM::Iterator gomItr2 = gom->begin();
		while (gomItr2 != end && gomItr2 != gomItr) {
			++gomItr2;
		}
		if(gomItr2 != end) ++gomItr2;
		

		for (; gomItr2 != end; ++gomItr2) {
			// gets the body and skips GOs that don't have one
			PhysicsBody* bodyComponent = gomItr2->GetComponent<PhysicsBody>();
			if (!bodyComponent) continue;
			
			glm::vec3 normal = glm::vec3();
			float depth = 0;
			if (CollisionTest::Test(gomItr->GetComponent<PhysicsBody>(), gomItr2->GetComponent<PhysicsBody>(), &normal, &depth)) {
				//std::cout << "[" << gomItr->GetName() << ", " << gomItr2->GetName() << "]\n";
				contact.AddCollision(
					gomItr->GetComponent<PhysicsBody>(), gomItr2->GetComponent<PhysicsBody>(), 
					normal, depth);
			}
		}
	}
}


void Physics::BroadcastCollisions() {
	const CollisionList* collisionList =
		contact.GetCollisionList();
	const CollisionList* collisionListLast =
		contact.GetCollisionListLast();

	for (CollisionInstance collision : *collisionList) {
		if (collisionListLast->find(collision.first) == collisionListLast->end()) {
			CollisionEnterEvent* e = new CollisionEnterEvent(
				collision.first.first->gameObject, collision.first.second->gameObject,
				collision.second.normal, collision.second.depth);
			
			eventManager->AddEvent(e);

			CollisionEnterEvent* e2 = new CollisionEnterEvent(
				collision.first.second->gameObject, collision.first.first->gameObject,
				-collision.second.normal, collision.second.depth);
			eventManager->AddEvent(e2);
		}
		else {
			CollisionEvent* e = new CollisionEvent(
				collision.first.first->gameObject, collision.first.second->gameObject,
				collision.second.normal, collision.second.depth);
			eventManager->AddEvent(e);

			CollisionEvent* e2 = new CollisionEvent(
				collision.first.second->gameObject, collision.first.first->gameObject,
				-collision.second.normal, collision.second.depth);
			eventManager->AddEvent(e2);
		}
	}

	for (CollisionInstance collision : *collisionListLast) {
		if (collisionList->find(collision.first) == collisionList->end()) {
			CollisionExitEvent* e = new CollisionExitEvent(
				collision.first.first->gameObject, collision.first.second->gameObject,
				collision.second.normal, collision.second.depth);
			eventManager->AddEvent(e);

			CollisionExitEvent* e2 = new CollisionExitEvent(
				collision.first.second->gameObject, collision.first.first->gameObject,
				-collision.second.normal, collision.second.depth);
			eventManager->AddEvent(e2);
		}
	}
	
}

PhysicsBody* Physics::GetCollision(GameObject* go) {
	PhysicsBody* body = go->GetComponent<PhysicsBody>();

	return contact.GetCollision(body);
}
std::vector<PhysicsBody*> Physics::GetAllCollisions(GameObject* go1) {
	PhysicsBody* body1 = go1->GetComponent<PhysicsBody>();
	std::vector<PhysicsBody*> bodys = contact.GetAllCollisions(body1);

	return bodys;
}

void Physics::RemoveGameObject(GameObject* gameObject) {
	contact.RemoveGameObject(gameObject);
}

void Physics::SetCollisionInteraction(int layer1, int layer2, bool interaction) {
	if (layer1 > layer2) {
		collisionTable[layer1][layer2] = interaction;
	}
	else {
		collisionTable[layer2][layer1] = interaction;
	}
}

bool Physics::LayerInteraction(int layer1, int layer2) {
	if (layer1 > layer2) {
		return collisionTable[layer1][layer2];
	}
	else {
		return collisionTable[layer2][layer1];
	}
}

void Physics::ExpandCollisionTable(int newSize) {
	collisionTable.push_back(std::vector<bool>(newSize, true));
}

