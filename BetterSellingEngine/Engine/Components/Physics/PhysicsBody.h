#pragma once

#include "../Component.h"
#include "../Transform.h"
#include "Shape.h"
#include "OBB.h"
#include "OBC2AA.h"
#include "OBC.h"
#include "Circle.h"
#include "CylinderAA.h"
#include "Sphere.h"

#include "../../GameObject.h"
class PhysicsBody : public Component {
public:
	std::string GetType() override { return "PhysicsBody"; };

	PhysicsBody(GameObject* go);
	~PhysicsBody();

	void SetMass(float newMass);

	void AddForce(glm::vec3 F) { force += F; }
	void SetVelocity(glm::vec3 newV) { velocity = newV; }
	glm::vec3 GetVelocity() { return velocity; }

	void AddAngularForce(float F) { angularForce += glm::vec3(0,0,F); }
	void SetAngularVelocity(glm::vec3 newAV) { angularVelocity = newAV; }
	glm::vec3 GetAngularVelocity(glm::vec3 newV) { return angularVelocity; }

	void SetHasGravity(bool newHas) { hasGravity = newHas; }

	void Integrate(float dt, float gravity);


	Shape::ShapeType GetShapeType() { return shape->GetShapeType(); }
	void SetOBB();
	void SetOBC2AA();
	void SetOBC();

	void SetCircle();

	void SetCylinderAA();
	void SetSphere();

private:
	Shape* shape = nullptr;

	Transform* transformComponent;

	glm::vec3 velocity = glm::vec3();
	glm::vec3 acceleration = glm::vec3();
	glm::vec3 force = glm::vec3();

	glm::vec3 angularAcceleration = glm::vec3();
	glm::vec3 angularVelocity = glm::vec3();
	glm::vec3 angularForce = glm::vec3();
	
	float mass = 1;
	float inverseMass = 1;

	bool hasGravity = true;
};