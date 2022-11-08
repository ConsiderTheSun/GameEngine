#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/vec2.hpp>
#include "../Geometry.h"


class TriangleMesh : public Geometry
{
public:
	TriangleMesh(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint,
		glm::vec2 firstTex, glm::vec2 secondTex, glm::vec2 thirdTex);

	GLuint GetVAO() override { return VAO; }
	GLuint GetVBO() override { return VBO; }
	GLsizei GetPointCount()override { return 3; }

private:
	GLuint VAO;
	GLuint VBO;
};


