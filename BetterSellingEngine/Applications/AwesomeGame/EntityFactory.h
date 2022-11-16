#pragma once

#include "../../Engine/engineIncludes.h"
#include "../../Engine/BetterSellingEngine.h"

class EntityFactory
{
public:
	static GameObject* MakeI(std::string name, glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 color = glm::vec3(1, 1, 1), int resolution = 30);

private:

};