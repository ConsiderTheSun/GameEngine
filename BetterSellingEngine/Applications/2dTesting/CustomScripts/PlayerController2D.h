#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/gtx/norm.hpp>
#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class PlayerController2D : public Script {
public:
	const float MAX_SPEED = 2.0f;
	const float ACC_SPEED = 0.01f;

	float deltaTime = 0;
	Camera::Dimensions dimentions = Camera::Dimensions::Two;

	Camera* mainCamera = Camera::MainCamera();

	GameObject* currentObject = NULL;
	GOM* gom = GOM::GetInstance();
	GOM::Iterator gomItr = gom->begin();
	GOM::Iterator end = gom->end();

	int currentObjectIndex = 0;

	PlayerController2D(GameObject* go) : Script(go) {}

	void TransformSet(Transform* objT);
	void BodySet(PhysicsBody* objB);

	void PlayerControls();

	void UpdateObject();
	void MoveObjectFollow();
	void SetColor();
	void Update(float dt) override;
};