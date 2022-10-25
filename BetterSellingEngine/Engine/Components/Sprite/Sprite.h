#pragma once

#include "../Component.h"
#include "Geometry.h"

#include "Meshes/TriangleMesh.h"
#include "Meshes/QuadMesh.h"
#include "Meshes/CubeMesh.h"

#include "Material.h"
#include "../Shader.h"
#include <type_traits>
#include <glm/glm/vec3.hpp>
class Sprite : public Component
{
public:
	std::string GetType() override { return "Sprite"; };

	Sprite(GameObject* go) : Component(go) {}
	~Sprite();

	void SetTriangleGeometry(glm::vec3 firstPoint = glm::vec3(-0.5f, -0.5f,0.0f),
		glm::vec3 secondPoint = glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3 thirdPoint = glm::vec3(0.0f, 0.5f, 0.0f),
		glm::vec2 firstTex = glm::vec2(0.0f,-0.0f),
		glm::vec2 secondTex = glm::vec2(1.0f, 0.0f),
		glm::vec2 thirdTex = glm::vec2(0.5f,1.0f));

	void SetQuadGeometry(glm::vec3 firstPoint = glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3 secondPoint = glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3 thirdPoint = glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3 fourthPoint = glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec2 firstTex = glm::vec2(1.0f, 1.0f),
		glm::vec2 secondTex = glm::vec2(1.0f, 0.0f),
		glm::vec2 thirdTex = glm::vec2(0.0f, 0.0f),
		glm::vec2 fourthTex = glm::vec2(0.0f, 1.0f));

	void SetCubeGeometry(float sideLenght = 1.0f);

	GLsizei PointCount() { return geometry->GetPointCount(); }
	const GLuint GetVAO() { return geometry->GetVAO(); }

	void SetColor(glm::vec3 newColor) { color = newColor; }
	const glm::vec3 GetColor() { return color; }

	bool SetMaterial(const char* texPath, bool noAlpha= false);
	const Material* GetMaterial() { return material; };
	const int GetMaterialID() { return material ? material->GetID(): -1; }

	void SetCustomShader(const char* vertPath = "Engine/default.vert", const char* fragPath = "Engine/default.frag");
	void RemoveCustomShader();
	Shader* GetCustomShader() { return customShader; }
private:
	Geometry* geometry = nullptr;
	Material* material = nullptr;

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	Shader* customShader = NULL;
};
