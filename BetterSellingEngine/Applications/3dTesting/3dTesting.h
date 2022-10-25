#pragma once

#include "../../Engine/engineIncludes.h"
#include "../../Engine/BetterSellingEngine.h"

#include "CustomScripts/PlayerController3D.h"
#include "CustomScripts/SillyThings.h"

#include "CustomScripts/WhenSadCollides3D.h"
#include "../SharedCustomScripts/PhysicsPlay.h"
class ThreeDTesting {
public:
	void Setup();
	void Start();
private:
	BetterSellingEngine* bse;

	void SpawnEntities();

	void SpawnGround();

	void SpawnFriendCube(glm::vec3 pos);
	void LikeStarsInTheSky();
};

