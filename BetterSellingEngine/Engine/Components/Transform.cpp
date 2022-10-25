#include "Transform.h"
#include "../GameObject.h"

Transform::Transform(GameObject* go, glm::vec3 position, glm::vec3 rotation, 
					 glm::vec3 scale): Component(go) {
	localPosition = position;
	localRotation = rotation;
	localScale = scale;
	worldPosition = position;
	worldRotation = rotation;
	worldScale = scale;
}

glm::mat4 Transform::GetRotationMatrix() {
	glm::mat4 rotationM = glm::rotate(glm::mat4(1.0f), worldRotation.x, glm::vec3(1, 0, 0));
	rotationM = glm::rotate(rotationM, worldRotation.y, glm::vec3(0, 1, 0));
	rotationM = glm::rotate(rotationM, worldRotation.z, glm::vec3(0, 0, 1));

	return rotationM;
}

const glm::vec3 Transform::SetPosition(glm::vec3 position) { 
	localPosition = position; 
	worldPosition = position; 
	
	if (gameObject) {
		GameObject* parent = gameObject->GetParent();
		if (parent) {
			Transform* parentTransform = parent->GetComponent<Transform>();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), parentTransform->GetWorldPosition());
			model *= parentTransform->GetRotationMatrix();
			model = glm::scale(model, parentTransform->GetWorldScale());
			worldPosition = model * glm::vec4(localPosition,1);
		}
		GameObject* child = gameObject->GetChild(0);
		int i = 0;
		while (child != NULL) {
			child->GetComponent<Transform>()->SetPosition(child->GetComponent<Transform>()->GetPosition());
			child = gameObject->GetChild(++i);
		}
	}

	return localPosition;
}
const glm::vec3 Transform::SetRotation(glm::vec3 rotation) { 
	localRotation = rotation; 
	worldRotation = rotation;
	if (gameObject) {
		GameObject* parent = gameObject->GetParent();
		if (parent) {
			Transform* parentTransform = parent->GetComponent<Transform>();
			worldRotation += parentTransform->GetWorldRotation();
		}

		GameObject* child = gameObject->GetChild(0);
		int i = 0;
		while (child != NULL) {
			child->GetComponent<Transform>()->SetRotation(child->GetComponent<Transform>()->GetRotation());
			child = gameObject->GetChild(++i);
		}
	}

	SetPosition(localPosition);
	return localRotation; 
}
const glm::vec3 Transform::SetScale(glm::vec3 scale) { 
	localScale = scale; 
	worldScale = scale;
	if (gameObject) {
		GameObject* parent = gameObject->GetParent();
		if (parent) {
			Transform* parentTransform = parent->GetComponent<Transform>();
			worldScale *= parentTransform->GetWorldScale();
		}

		GameObject* child = gameObject->GetChild(0);
		int i = 0;
		while (child != NULL) {
			child->GetComponent<Transform>()->SetScale(child->GetComponent<Transform>()->GetScale());
			child = gameObject->GetChild(++i);
		}
	}
	SetPosition(localPosition);
	return localScale; 
}
const glm::vec3 Transform::SetWorldPosition(glm::vec3 position) {
	localPosition = position;
	worldPosition = position;

	if (gameObject) {
		GameObject* parent = gameObject->GetParent();
		if (parent) {
			Transform* parentTransform = parent->GetComponent<Transform>();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), parentTransform->GetWorldPosition());
			model *= parentTransform->GetRotationMatrix();
			model = glm::scale(model, parentTransform->GetWorldScale());

			localPosition = glm::transpose( glm::inverseTranspose(model)) * glm::vec4(worldPosition, 1);
		}
		GameObject* child = gameObject->GetChild(0);
		int i = 0;
		while (child != NULL) {
			child->GetComponent<Transform>()->SetPosition(child->GetComponent<Transform>()->GetPosition());
			child = gameObject->GetChild(++i);
		}
	}

	return localPosition;
}