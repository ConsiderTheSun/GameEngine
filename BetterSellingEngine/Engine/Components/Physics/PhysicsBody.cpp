#include "PhysicsBody.h"

PhysicsBody::PhysicsBody(GameObject* go) : Component(go) {
	transformComponent = gameObject->GetComponent<Transform>();
}

PhysicsBody::~PhysicsBody() {
	if (shape) {
		delete(shape);
		shape = nullptr;
	}
}

void PhysicsBody::SetMass(float newMass) {
	mass = newMass;
	inverseMass = 1.0f / newMass;
}

void PhysicsBody::Integrate(float gravity) {
	if (hasGravity) {
		force.y -= gravity * mass;
	}
	
	acceleration = force * inverseMass;
	velocity += acceleration;
	glm::vec3 deltaPosition = velocity;
	glm::vec3 oldPosition = transformComponent->GetPosition();

	angularAcceleration = angularForce * inverseMass;
	angularVelocity += angularAcceleration;
	glm::vec3 deltaRotation = angularVelocity;
	glm::vec3 oldRotation = transformComponent->GetRotation();

	transformComponent->SetPosition(oldPosition + deltaPosition);
	transformComponent->SetRotation(oldRotation + deltaRotation);

	force = glm::vec3();
	angularForce = glm::vec3();
}

void PhysicsBody::SetOBB() {
	shape = new OBB();
}
void PhysicsBody::SetOBC2AA() {
	shape = new OBC2AA();
}
void PhysicsBody::SetOBC() {
	shape = new OBC();
}

void PhysicsBody::SetCircle() {
	shape = new Circle();
}