#include "EntityFactory.h"

#define _USE_MATH_DEFINES
#include <math.h>

BetterSellingEngine* EntityFactory::bse = BetterSellingEngine::GetInstance();

GameObject* EntityFactory::MakeI(std::string name, std::string layerName, 
								 glm::vec3 position, glm::vec3 color, int resolution) {

	GameObject* entityBody = new GameObject(name + " Body");

	entityBody->SetLayer(layerName);

	entityBody->AddComponent<Sprite>();

	Sprite* sprite = entityBody->GetComponent<Sprite>();
	sprite->SetCylinderGeometry(2 * resolution);
	sprite->SetColor(0.8f * color);

	Transform* transform = entityBody->GetComponent<Transform>();

	transform->SetPosition(position);
	transform->SetRotation(glm::vec3(-M_PI / 2, 0, 0));

	PhysicsBody* entityB = entityBody->AddComponent<PhysicsBody>();
	entityB->SetCylinderAA();
	entityB->SetHasGravity(false);

	bse->AddGameObject(entityBody);


	GameObject* entityBodyTop = new GameObject(name + " Body Top");

	entityBodyTop->AddComponent<Sprite>();

	sprite = entityBodyTop->GetComponent<Sprite>();
	sprite->SetSphereGeometry(resolution);
	sprite->SetColor(0.8f * color);

	transform = entityBodyTop->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, 0, 0.5));

	bse->AddGameObject(entityBodyTop, entityBody);


	GameObject* entityHead = new GameObject(name + " Head");

	entityHead->AddComponent<Sprite>();

	sprite = entityHead->GetComponent<Sprite>();
	sprite->SetSphereGeometry(resolution);
	sprite->SetColor(color);

	transform = entityHead->GetComponent<Transform>();
	transform->SetPosition(glm::vec3(0, 0, 1.5));

	bse->AddGameObject(entityHead, entityBody);

	return entityBody;

}


GameObject* EntityFactory::MakeProjectile(std::string name, std::string layerName,
										  glm::vec3 position, float scale,
										  glm::vec3 color,
										  glm::vec3 velocity, glm::vec3 acc,
										  int resolution) {

	GameObject* projectileGO = new GameObject(name);
	projectileGO->AddComponent<Sprite>();

	projectileGO->SetLayer(layerName);

	Sprite* projectileSprite = projectileGO->GetComponent<Sprite>();
	projectileSprite->SetSphereGeometry();
	projectileSprite->SetColor(color);

	Transform* projectileTransform = projectileGO->GetComponent<Transform>();

	projectileTransform->SetPosition(position);
	projectileTransform->SetScale(glm::vec3(scale, scale, scale));

	PhysicsBody* projectileBody = projectileGO->AddComponent<PhysicsBody>();
	projectileBody->SetSphere();
	projectileBody->SetVelocity(velocity);

	projectileBody->SetMass(0.00001);

	projectileGO->AddComponent<ProjectileController>();

	bse->AddGameObject(projectileGO);

	return projectileGO;
}
