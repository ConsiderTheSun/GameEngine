#include "Sprite.h"

Sprite::~Sprite() {
	free(geometry);
	free(material);
	free(customShader);

	geometry = nullptr;
	material = nullptr;
}

void Sprite::SetTriangleGeometry(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint, 
								 glm::vec2 firstTex, glm::vec2 secondTex, glm::vec2 thirdTex) {
	// if a geometry already exists, delete it
	if (geometry) {
		free(geometry);
	}
	geometry = new TriangleMesh(firstPoint, secondPoint, thirdPoint, firstTex, secondTex, thirdTex);
}

void Sprite::SetQuadGeometry(glm::vec3 firstPoint, glm::vec3 secondPoint,
		glm::vec3 thirdPoint, glm::vec3 fourthPoint, glm::vec2 firstTex,
		glm::vec2 secondTex, glm::vec2 thirdTex,glm::vec2 fourthTex) {
	// if a geometry already exists, delete it
	if (geometry) {
		free(geometry);
	}
	geometry = new QuadMesh(firstPoint, secondPoint, thirdPoint, fourthPoint, firstTex, secondTex, thirdTex, fourthTex);
}

void Sprite::SetCubeGeometry(float sideLenght) {
	geometry = new CubeMesh(sideLenght);
}

void Sprite::SetCircleGeometry(int resolution) {
	geometry = new CircleMesh(resolution);
}

void Sprite::SetCylinderGeometry(int resolution) {
	geometry = new CylinderMesh(resolution);
}

void Sprite::SetSphereGeometry(int resolution) {
	geometry = new SphereMesh(resolution);
}

bool Sprite::SetMaterial(const char* texPath, bool noAlpha) { 
	// creates the new sprite and checks if it was created properly
	Material* newMaterial = new Material(texPath, noAlpha);
	if (newMaterial->InitializationError()) {
		return false;
	}

	// updates the material
	free(material);
	material = newMaterial;
	return true;
}

void Sprite::SetCustomShader(const char* vertPath, const char* fragPath) {
	free(customShader);
	customShader = new Shader(vertPath, fragPath);
}
void Sprite::RemoveCustomShader() {
	free(customShader);
	customShader = NULL;
}

Sprite::Mesh Sprite::StringToMesh(std::string meshName) {
	if (meshName == "triangle") return Triangle;
	if (meshName == "quad")		return Quad;
	if (meshName == "cube")		return Cube;
	if (meshName == "circle")	return Circle;
	if (meshName == "cylinder") return Cylinder;

	return Triangle;
}
