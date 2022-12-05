#include "PlayerController.h"

#include <glm/glm/gtx/string_cast.hpp>


//#include "EnemyManager.h"

GameObject* PlayerController::currentPlatform = nullptr;
GameObject* PlayerController::previousPlatform = nullptr;

PlayerController::PlayerController(GameObject* go) : Script(go) {
	playerTransform = gameObject->GetComponent<Transform>();
	playerPhysicsBody = gameObject->GetComponent<PhysicsBody>();
}

void PlayerController::Update(float dt) {
	glm::vec3 lightPos = gameObject->transform->GetWorldPosition() +glm::vec3(0, 3, 0);
	BetterSellingEngine::GetInstance()->SetLightPosition(lightPos);

	if (gameObject->transform->GetWorldPosition().y < -4) {
		BetterSellingEngine::GetInstance()->ChangeScene(new GameOverScene());
	}
	Move(dt);

	Shoot(dt);

	if (invincible) {
		UpdateInvincibility(dt);
	}
}

void PlayerController::Move(float dt) {
	PhysicsBody* body = gameObject->GetComponent<PhysicsBody>();

	float rotationSpeed = 1.0 / 500;
	glm::vec3 deltaRotation = glm::vec3(0, 0, -rotationSpeed * Input::DeltaMouse().x);
	playerTransform->SetRotation(playerTransform->GetRotation() + deltaRotation);

	glm::vec3 deltaPos = glm::vec3(0, 0, 0);
	bool moving = false;
	if (Input::KeyDown(GLFW_KEY_W) == Input::State::Down) {
		deltaPos = playerTransform->Up();
		moving = true;
	}
	else if (Input::KeyDown(GLFW_KEY_S) == Input::State::Down) {
		deltaPos = playerTransform->Down();
		moving = true;
	}

	if (Input::KeyDown(GLFW_KEY_A) == Input::State::Down) {
		deltaPos += playerTransform->Left();
		moving = true;
	}
	else if (Input::KeyDown(GLFW_KEY_D) == Input::State::Down) {
		deltaPos += playerTransform->Right();
		moving = true;
	}

	
	if (moving) {
		deltaPos = SPEED * glm::normalize(deltaPos);
	}
	else{
		deltaPos *= -SPEED * body->GetVelocity();
		deltaPos.y = 0;
	}

	


	deltaPos.y = body->GetVelocity().y;

	if (jumpCount < 2 && Input::KeyDown(GLFW_KEY_SPACE) == Input::State::Enter) {
		//body->AddForce(1.0f / 10 * glm::vec3(0, 1, 0));
		//body->AddForce(5.0f* glm::vec3(0, 1, 0));
		//deltaPos.y = 2.0f * dt;
		//deltaPos.y = 0.02f;
		deltaPos.y = 3.0f;
		++jumpCount;
		falling = false;
	}

	if (jumpCount && !falling && deltaPos.y <= 0) {
		falling = true;
		//std::cout << "zenith\n";
	}

	if (falling) {
		glm::vec3 gravity = glm::vec3(0, -Physics::GetInstance()->GetGravity()*MASS,0);
		body->AddForce(gravity);
	}

	body->SetVelocity(deltaPos);
}

void PlayerController::Shoot(float dt) {
	
	if (shootCooldown <= 0 && Input::KeyDown(GLFW_MOUSE_BUTTON_LEFT) == Input::State::Down) {
		shootCooldown = SHOT_RATE;

		glm::vec3 projPos = gameObject->GetComponent<Transform>()->GetPosition();
		projPos += 0.65f * playerTransform->Up();
		projPos += glm::vec3(0, 0.5, 0);
		glm::vec3 projColor = glm::vec3(0.6, 0.2, 0.2);
		float movementBoost = glm::dot(playerPhysicsBody->GetVelocity(), playerTransform->Up());
		if (movementBoost < 0) movementBoost = 0;
		//glm::vec3 projVelocity = playerPhysicsBody->GetVelocity() + 0.01f * playerTransform->Up();
		glm::vec3 projVelocity = (movementBoost + SHOT_SPEED) * playerTransform->Up();
		glm::vec3 projAcc = glm::vec3(0, 0, 0);
		EntityFactory::MakeProjectile("Projectile", "Projectile Layer", projPos, 0.3f, projColor, projVelocity, projAcc);
	}
	else {
		shootCooldown -= dt;
	}
}

void PlayerController::UpdateInvincibility(float dt) {
	invincibilityCounter -= dt;

	if (invincibilityCounter <= 0) {
		invincible = false;

		gameObject->GetComponent<Sprite>()->SetColor(playerColor);

		for (GameObject* go : gameObject->getChildrenList()) {
			go->GetComponent<Sprite>()->SetColor(playerColor);
		}
	}
}

void PlayerController::TakeDamage() {
	--health;

	if (health <= 0) {
		BetterSellingEngine::GetInstance()->ChangeScene(new GameOverScene());
	}

	invincible = true;

	invincibilityCounter = INVINCIBILITY_TIME;

	gameObject->GetComponent<Sprite>()->SetColor(DAMAGE_COLOR);

	for (GameObject* go : gameObject->getChildrenList()) {
		go->GetComponent<Sprite>()->SetColor(DAMAGE_COLOR);
	}
}



std::chrono::steady_clock::time_point tempCounter;
void PlayerController::OnCollisionEnter(CollisionEvent* e) {

	// if the player is hit, take damage and destroy the enemy
	if (e->collisionObject->GetLayerName() == "Enemy Layer") {
		if (!e->collisionObject->GetParent()) {
			EnemyManager::RemoveEnemy(e->collisionObject);
		}
		else {
			GameObject::Destroy(e->collisionObject);
		}
		for (GameObject* root = e->collisionObject; root->GetParent();) {
			root = root->GetParent();
			EnemyManager::RemoveEnemy(root);
		}
		TakeDamage();
	}
	else if (e->collisionObject->GetLayerName() == "Ground Layer") {
		
		if (1 - glm::dot(e->normal, glm::vec3(0, -1, 0)) < 0.0001f) {
			falling = false;
			jumpCount = 0;
			currentPlatform = e->collisionObject;
			gameObject->GetComponent<PhysicsBody>()->SetHasGravity(false);
			glm::vec3 noFall = gameObject->GetComponent<PhysicsBody>()->GetVelocity();
			noFall.y = 0;
			gameObject->GetComponent<PhysicsBody>()->SetVelocity(noFall);
		}
		else {
			glm::vec3 offset = gameObject->transform->GetPosition() + e->depth * e->normal;
			gameObject->transform->SetPosition(offset);
		}
		
	}
	else if (e->collisionObject->GetLayerName() == "Victory Layer") {
		GameObject::Destroy(e->collisionObject);
		if (++victoryPoints >= victoryRequirement) {
			GameOverScene* winScene = new GameOverScene();
			winScene->win = true;

			BetterSellingEngine::GetInstance()->ChangeScene(winScene);
		}
	}
}

void PlayerController::OnCollision(CollisionEvent* e) {
	if (e->collisionObject->GetLayerName() == "Ground Layer") {
		if (e->depth > 0.01f) {
			glm::vec3 offset = gameObject->transform->GetPosition() - e->depth * e->normal;
			gameObject->transform->SetPosition(offset);
		}
	}
}

void PlayerController::OnCollisionExit(CollisionEvent* e) {

	if (e->collisionObject->GetLayerName() == "Ground Layer") {
		if (currentPlatform != e->collisionObject) return;
		//std::cout << "take off!\n";
		tempCounter = std::chrono::steady_clock::now();
		falling = false;
		if(!jumpCount) jumpCount=1;
		previousPlatform = currentPlatform;
		currentPlatform = nullptr;

		gameObject->GetComponent<PhysicsBody>()->SetHasGravity(true);
	}

}