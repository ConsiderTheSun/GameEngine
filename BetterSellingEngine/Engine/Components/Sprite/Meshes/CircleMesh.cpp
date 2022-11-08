#include "CircleMesh.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

CircleMesh::CircleMesh(int resolution) :pointCount(3* resolution) {

	glGenVertexArrays(1, &VAO);

	GLuint EBO;

	int vertCount = (resolution + 1) * 5;
	float* vertices = new float[vertCount]();
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0;
	vertices[3] = 0.5;
	vertices[4] = 0.5;

	float deltaTheta = 2*M_PI / resolution;
	float theta = 0;
	for (int i = 1; i < resolution + 1; ++i) {
		vertices[5 * i] = 0.5f*cos(theta);
		vertices[5 * i + 1] = 0.5*sin(theta);
		vertices[5 * i + 2] = 0;
		vertices[5 * i + 3] = 0.5f * cos(theta)+0.5;
		vertices[5 * i + 4] = 0.5 * sin(theta)+0.5;

		theta += deltaTheta;
	}

	unsigned int* indices = new unsigned int[3*resolution]();

	for (int i = 0; i < resolution-1; i++) {
		indices[3*i] = 0;
		indices[3*i+1] = i+1;
		indices[3*i+2] = i+2;
	}
	indices[3*(resolution-1)] = 0;
	indices[(3 * (resolution-1))+1] = resolution;
	indices[(3 * (resolution-1))+2] = 1;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(unsigned int)*resolution, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	delete[] vertices;
	delete[] indices;
}