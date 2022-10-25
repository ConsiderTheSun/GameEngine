#pragma once
#include "../../Engine/BetterSellingEngine.h"
#include "../../Engine/engineIncludes.h"

class SillyThings : public Script {
public:
	SillyThings(GameObject* go) : Script(go) {}
	static GameObject* SpawnSadFriend(glm::vec3 pos);
private:
	
	void Update(float dt) override;

};