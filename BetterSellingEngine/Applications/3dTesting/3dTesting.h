#pragma once

#include "../../Engine/engineIncludes.h"
#include "../../Engine/BetterSellingEngine.h"

#include "CustomScripts/PlayerController3D.h"
#include "CustomScripts/SillyThings.h"

#include "CustomScripts/WhenSadCollides3D.h"
#include "../SharedCustomScripts/PhysicsPlay.h"

#include "CustomScripts/SunController.h"

#include "CustomScripts/CylinderTester.h"

class ThreeDTesting {
public:
	void Setup();
	void Start();
private:
	BetterSellingEngine* bse;
	void LetThereBeLight();
	void SpawnEntities();

	void SpawnGround();

	void SpawnFriendCube(glm::vec3 pos);
	void LikeStarsInTheSky();

	void SpawnCylinderThing();

	void ThesePlainPlanes();

	void ACircleBut3D();
};

