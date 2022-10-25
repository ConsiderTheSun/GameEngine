#include "PhysicsPlay.h"

PhysicsPlay::PhysicsPlay(GameObject* go) : Script(go) {
	body = gameObject->GetComponent<PhysicsBody>();
	if (!body) {
		std::cerr << "error: no physics body\n" << std::endl;
	}
}

void PhysicsPlay::Update(float dt) {
	if (Input::KeyDown(GLFW_KEY_MINUS) == Input::State::Down) {
		physicsSystem->SetGravity(-physicsSystem->GetGravity());
	}

	if (Input::KeyDown(GLFW_KEY_0) == Input::State::Down) {
		physicsSystem->SetGravity(0);
		noGravity = true;
	}
	if (Input::KeyDown(GLFW_KEY_1) == Input::State::Down) {
		physicsSystem->SetGravity(0.00001f);
		noGravity = false;
	}
}

void PhysicsPlay::OnCollisionEnter(CollisionEvent* e) {
	PhysicsBody* collisionBody = e->collisionObject->GetComponent<PhysicsBody>();
	if (!noGravity) {
		collisionBody->SetVelocity(glm::vec3());
	}

	collisionBody->SetAngularVelocity(glm::vec3(0, 0, 0.005));
}

void PhysicsPlay::OnCollision(CollisionEvent* e) {
	PhysicsBody* collisionBody = e->collisionObject->GetComponent<PhysicsBody>();

	if (noGravity) {
		glm::vec3 dir = e->collisionObject->GetComponent<Transform>()->GetPosition();
		dir -= gameObject->GetComponent<Transform>()->GetPosition();
		dir = glm::normalize(dir);
		collisionBody->AddForce(0.00001f * dir);
	}

	collisionBody->AddAngularForce(-0.00001f);
}

void PhysicsPlay::OnCollisionExit(CollisionEvent* e) {
	PhysicsBody* collisionBody = e->collisionObject->GetComponent<PhysicsBody>();

	collisionBody->SetAngularVelocity(glm::vec3());
	
}