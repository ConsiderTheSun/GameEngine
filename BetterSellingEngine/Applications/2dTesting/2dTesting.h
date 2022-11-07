#pragma once

#include "../../Engine/engineIncludes.h"
#include "../../Engine/BetterSellingEngine.h"

#include "CustomScripts/PlayerController2D.h"

#include "CustomScripts/WhenSadCollides2D.h"
#include "../SharedCustomScripts/PhysicsPlay.h"

class TwoDTesting {
public:
	void Setup();
	void Start();

private:
	BetterSellingEngine* bse;

	void OneSegy(glm::vec3 position, float mass = 1);
	void SegyFriends();
	void GlitchyFriends();
	void GarfTris();
	void CircleBuddy();
	void SpawnEntities();

};