#include "ScriptManager.h"

void ScriptManager::Update(GOM* gom, float dt) {
	for (GOM::Iterator gomItr = gom->begin(), end = gom->end(); gomItr != end; ++gomItr) {
		// gets the scripts and skips GOs that don't have one
		std::vector<Script*> scriptComponents = gomItr->GetAllComponents<Script>();

		for (Script* component : scriptComponents) {
			component->Update(dt);
		}
	}
}