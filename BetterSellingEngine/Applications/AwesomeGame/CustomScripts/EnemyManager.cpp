#include "EnemyManager.h"

void EnemyManager::Update(float dt) {

	if (Input::KeyDown(GLFW_MOUSE_BUTTON_RIGHT) == Input::State::Enter) {
		std::cout << "clicky\n";
		GameObject* enemyGO = EntityFactory::MakeI("Enemy", glm::vec3(5, 0, 5), glm::vec3(0.0, 1, 0.0));
	}
}