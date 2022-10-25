#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class PlayerController3D : public Script {
public:

	Camera* mainCamera = Camera::MainCamera();

	GameObject* currentObject = NULL;
	GOM* gom = GOM::GetInstance();
	GOM::Iterator gomItr = gom->begin();
	GOM::Iterator end = gom->end();

	int currentObjectIndex = 0;

	PlayerController3D(GameObject* go) : Script(go) {}


	void PlayerControls3D(float dt);

	void UpdateObject();
	void MoveObjectSeperate();

	void Update(float dt) override;
};