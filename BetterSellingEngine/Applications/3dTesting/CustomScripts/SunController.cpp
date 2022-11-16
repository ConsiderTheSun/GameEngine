#include "SunController.h"

#include <glm/glm/gtx/string_cast.hpp>

void SunController::Update(float dt) {
	//std::cout << "sun Pos: " << glm::to_string(gameObject->GetComponent<Transform>()->GetWorldPosition()) << std::endl;

	bse->SetLightPosition(gameObject->GetComponent<Transform>()->GetWorldPosition());

}