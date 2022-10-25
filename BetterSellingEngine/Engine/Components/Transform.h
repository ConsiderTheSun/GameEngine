#pragma once

#include "Component.h"

#include <glm/glm/mat4x4.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/matrix_inverse.hpp>
class Transform : public Component{
public:
	std::string GetType() override { return "Transform"; };

	Transform(GameObject* go = NULL, glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 rotation = glm::vec3(0, 0, 0),
		glm::vec3 scale = glm::vec3(1, 1, 1));

	glm::mat4 GetRotationMatrix();

	glm::vec3 Right() { return GetRotationMatrix() * glm::vec4(1, 0, 0, 1); }
	glm::vec3 Up() { return GetRotationMatrix() * glm::vec4(0, 1, 0, 1); }
	glm::vec3 Forward() { return GetRotationMatrix() * glm::vec4(0, 0, 1, 1); }

	glm::vec3 Left() { return -Right(); }
	glm::vec3 Down() { return -Up(); }
	glm::vec3 Back() { return -Forward(); }

	const glm::vec3 GetPosition() { return localPosition; }
	const glm::vec3 GetRotation() { return localRotation; }
	const glm::vec3 GetScale() { return localScale; }

	const glm::vec3 GetWorldPosition() { return worldPosition; }
	const glm::vec3 GetWorldRotation() { return worldRotation; }
	const glm::vec3 GetWorldScale() { return worldScale; }


	const glm::vec3 SetPosition(glm::vec3 position);
	const glm::vec3 SetRotation(glm::vec3 rotation);
	const glm::vec3 SetScale(glm::vec3 scale);

	const glm::vec3 SetWorldPosition(glm::vec3 position);

private:
	glm::vec3 localPosition;
	glm::vec3 localRotation;
	glm::vec3 localScale;

	glm::vec3 worldPosition;
	glm::vec3 worldRotation;
	glm::vec3 worldScale;
};