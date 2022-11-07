#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/vec2.hpp>
#include "../Geometry.h"


class CylinderMesh : public Geometry
{
public:
	CylinderMesh(int resolution);

	GLuint GetVAO() override { return VAO; }
	GLsizei GetPointCount()override { return pointCount; }

private:
	GLuint VAO;
	int pointCount;
};


