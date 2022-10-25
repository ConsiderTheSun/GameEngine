#pragma once
#include "Components/Transform.h"
#include <glm/glm/mat4x4.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

class Camera {
public:
	enum Dimensions { Two, Three };

	static Camera* GetInstance(Dimensions d = Two);
	static Camera* MainCamera();

	
	
	Transform transform;
	glm::vec3 lookDirection;

	float pitch = 0.0;
	float yaw = -90.0f;

	Camera(Dimensions d = Two);

	void Update();
	const glm::vec3 GetLook() { return lookDirection; }
	const glm::mat4* GetView() const;
	const glm::mat4* GetProjection() const;
private:
	static Camera* camInstance;

	Dimensions dimensions;

	glm::mat4 view;
	glm::mat4 projection;
};