#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/vec2.hpp>
#include "../Geometry.h"

class SphereMesh : public Geometry
{
public:
	SphereMesh(int resolution);

	GLuint GetVAO() override { return VAO; }
	GLuint GetVBO() override { return VBO; }

	GLsizei GetPointCount()override { return pointCount; }

private:
	GLuint VAO;
	GLuint VBO;
	int pointCount;
};