#pragma once

#include <glm/glm/vec3.hpp>

#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

#include <deque>

typedef std::deque<std::pair<GameObject*, bool>> PlatformComparisonList;
typedef std::unordered_map<GameObject*, PlatformComparisonList> PlatformContainer;
class PlatformManager : public Script {
public:
	PlatformManager(GameObject* go) : Script(go) { }
	void AddComparison(GameObject* currentGO, GameObject* checkGO, PlatformComparisonList& comparisonList);
	void AddPlatform(GameObject* go);

	bool noIntersections(GameObject* platform,glm::vec3 pos, float radius);

private:
	PlatformContainer platformContainer;
};