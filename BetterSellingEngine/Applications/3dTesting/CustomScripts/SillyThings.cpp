#include "SillyThings.h"

void SillyThings::Update(float dt) {

	if (Input::KeyDown(GLFW_MOUSE_BUTTON_LEFT) == Input::State::Enter) {
		Camera* mainCamera = Camera::MainCamera();

		glm::vec3 inFront = mainCamera->transform.GetPosition() 
			+ 2.0f*mainCamera->GetLook();
		SpawnSadFriend(glm::vec3(inFront));
	}
	
}

GameObject* SillyThings::SpawnSadFriend(glm::vec3 pos) {
	BetterSellingEngine* bse = BetterSellingEngine::GetInstance();

	GameObject* cubeFriend = new GameObject("Cube==Sad");

	cubeFriend->AddComponent<Sprite>();

	Sprite* cubeySprite = cubeFriend->GetComponent<Sprite>();
	cubeySprite->SetCubeGeometry();
	cubeySprite->SetColor(glm::vec3(1, 1, 1));
	cubeySprite->SetMaterial("./assets/sad.png");

	Transform* cubeyT = cubeFriend->GetComponent<Transform>();

	cubeyT->SetPosition(pos);

	cubeFriend->AddComponent<PhysicsBody>()->SetOBC();

	bse->AddGameObject(cubeFriend);

	return cubeFriend;
}