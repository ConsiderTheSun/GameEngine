#include "EntityFactory.h"

GameObject* EntityFactory::MakeI(std::string name, glm::vec3 position, glm::vec3 color, int resolution) {
	BetterSellingEngine* bse = BetterSellingEngine::GetInstance();

	GameObject* entityBody = new GameObject(name + " Body");

	entityBody->AddComponent<Sprite>();

	Sprite* sprite = entityBody->GetComponent<Sprite>();
	sprite->SetCylinderGeometry(2 * resolution);
	//sprite->SetCubeGeometry();
	sprite->SetColor(0.8f * color);

	Transform* transform = entityBody->GetComponent<Transform>();

	transform->SetPosition(position);
	transform->SetRotation(glm::vec3(-3.14 / 2, 0, 0));


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
