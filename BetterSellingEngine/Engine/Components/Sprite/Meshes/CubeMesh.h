#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/vec2.hpp>
#include "../Geometry.h"


class CubeMesh : public Geometry
{
public:
	CubeMesh(float sizeLength = 1);
	GLuint GetVAO() override { return cubeVAO; }
	GLsizei GetPointCount()override { return 36; }

private:
	static GLuint cubeVAO;
};


