#include "PlatformManager.h"

#include <glm/glm/gtx/string_cast.hpp>

void PlatformManager::AddComparison(GameObject* currentGO, GameObject* checkGO, PlatformComparisonList& comparisonList) {
	bool intersect = false;

	glm::vec3 currentPos = currentGO->transform->GetWorldPosition();
	glm::vec3 currentScale = 0.5f*currentGO->transform->GetWorldScale();

	glm::vec3 checkPos = checkGO->transform->GetWorldPosition();
	glm::vec3 checkScale = 0.5f*checkGO->transform->GetWorldScale();

	float heightDifference = (checkPos.y - checkScale.z) - (currentPos.y + currentScale.z);
	if (heightDifference > 0 && heightDifference < 4) {

		glm::vec2 diff = glm::vec2(checkPos.x - currentPos.x, checkPos.z - currentPos.z);
		float rSquared = checkScale.x + currentScale.x;
		rSquared *= rSquared;
		if (glm::dot(diff, diff) < rSquared) {
			intersect = true;
		}
	}
	comparisonList.push_back(std::make_pair(checkGO, intersect));
}
void PlatformManager::AddPlatform(GameObject* go) {
	Transform* goTransform = go->transform;

	PlatformComparisonList comparisonList = PlatformComparisonList();

	PlatformContainer::iterator itr = platformContainer.begin();

	for (; itr != platformContainer.end(); ++itr) {
		AddComparison(go, itr->first, comparisonList);
		AddComparison(itr->first, go, itr->second);
	}
	platformContainer.insert(std::pair<GameObject*, PlatformComparisonList>(go, comparisonList));
	/*
	std::cout << "current Map: \n";
	for (auto outerElement : platformContainer) {
		std::cout << "  platform at: " << glm::to_string((outerElement.first)->transform->GetPosition()) << std::endl;
		
		for (auto innerElement : outerElement.second) {
			std::cout << "    pos: " << glm::to_string(innerElement.first->transform->GetPosition()) <<
				" intersect: " << innerElement.second << std::endl;
		}
	}
	*/
}

bool PlatformManager::noIntersections(GameObject* platform, glm::vec3 pos, float radius) {
	
	
	for (auto element : platformContainer[platform]) {
		if (element.second) {
			glm::vec3 platformPos = element.first->transform->GetWorldPosition();
			float platformRadius = element.first->transform->GetWorldScale().x/2;
			glm::vec2 diff = glm::vec2(platformPos.x - pos.x, platformPos.z - pos.z);
			float rSquared = platformRadius + radius;
			rSquared *= rSquared;
			if (glm::dot(diff, diff) < rSquared) {
				return false;
			}

		}
	}
	
	return true;
}
