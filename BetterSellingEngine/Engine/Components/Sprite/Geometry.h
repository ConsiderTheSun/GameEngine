#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Geometry {
public:
	virtual GLuint GetVAO() = 0;
	virtual GLuint GetVBO() = 0;
	virtual GLsizei GetPointCount() = 0;
};