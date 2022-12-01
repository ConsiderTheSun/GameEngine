#pragma once

#include "../../Engine/engineIncludes.h"
#include "../../Engine/BetterSellingEngine.h"

#include "CustomScripts/ProjectileController.h"
class EntityFactory
{
public:
	static GameObject* MakeI(std::string name, std::string layerName, 
		glm::vec3 position = glm::vec3(0, 0, 0), glm::vec3 color = glm::vec3(1, 1, 1), 
		int resolution = 30);

	static GameObject* MakeProjectile(std::string name, std::string layerName, 
		glm::vec3 position = glm::vec3(0, 0, 0), float scale = 0.2, glm::vec3 color = glm::vec3(1, 1, 1), 
		glm::vec3 velocity = glm::vec3(0,0,0), glm::vec3 acc = glm::vec3(0,0,0),
		int resolution = 30);

	static BetterSellingEngine* bse;

private:

};