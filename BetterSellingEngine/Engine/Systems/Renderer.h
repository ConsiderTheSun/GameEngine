#pragma once

#include "GameObjectManager.h"
#include "../GameObject.h"
#include "../Shader.h"
#include "../Camera.h"

class Renderer
{
public:
	void Init();
	~Renderer();

	void Draw(const Camera* renderCam, GOM* gom);

	void EnableLighting() { useLight = true; }
	void DisableLighting() { useLight = false; }
	void SetLightPosition(glm::vec3 newPos) { lightPos = newPos; }
	glm::vec3 GetLightPosition() { return lightPos; }

	void Reset() { useLight = false; lightPos = glm::vec3(0, 0, 0);}

	void SetBackgroundColor(glm::vec3 color) { backgroundColor = color; }
private:
	Shader* defaultShader;

	bool useLight = false;
	glm::vec3 lightPos = glm::vec3(0, 0, 0);

	glm::vec3 backgroundColor = glm::vec3(0,0,0);
};

