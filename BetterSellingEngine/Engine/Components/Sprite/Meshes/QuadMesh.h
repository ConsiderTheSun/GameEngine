#pragma once

#include <glm/glm/vec3.hpp>
#include <glm/glm/vec2.hpp>
#include "../Geometry.h"


class QuadMesh : public Geometry
{
public:
	QuadMesh(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint, glm::vec3 fourthPoint,
		glm::vec2 firstTex, glm::vec2 secondTex, glm::vec2 thirdTex, glm::vec2 fourthTex);

	GLuint GetVAO() override { return VAO; }
	GLuint GetVBO() override { return VBO; }

	GLsizei GetPointCount()override { return 6; }

private:
	GLuint VAO;
	GLuint VBO;
};


