#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class CameraController : public Script {
public:

	void SetFollowObject(GameObject* _followGO) {
		followGO = _followGO; followTransform = followGO->GetComponent<Transform>();
	}

	CameraController(GameObject* go) : Script(go) {}

	void Update(float dt) override;

private:
	Camera* mainCamera = Camera::MainCamera();

	GameObject* followGO = nullptr;
	Transform* followTransform = nullptr;

	float currentDistance = 5;
};