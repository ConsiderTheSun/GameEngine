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

private:
	Shader* defaultShader;
};

