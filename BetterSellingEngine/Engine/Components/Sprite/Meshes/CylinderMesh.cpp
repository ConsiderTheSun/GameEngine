#include "CylinderMesh.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

CylinderMesh::CylinderMesh(int resolution) :pointCount(3 * 4* resolution) {

	glGenVertexArrays(1, &VAO);

	GLuint EBO;

	int vertCount = 2 * (resolution + 1) * 5;
	float* vertices = new float[vertCount]();
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0.5;
	vertices[3] = 0.5;
	vertices[4] = 0.5;

	float deltaTheta = 2 * M_PI / resolution;
	float theta = 0;
	for (int i = 1; i < resolution + 1; ++i) {
		vertices[5 * i] = 0.5f * cos(theta);
		vertices[5 * i + 1] = 0.5 * sin(theta);
		vertices[5 * i + 2] = 0.5;
		vertices[5 * i + 3] = 0.5f * cos(theta) + 0.5;
		vertices[5 * i + 4] = 0.5 * sin(theta) + 0.5;

		theta += deltaTheta;
	}

	// face 2
	for (int i = resolution+1; i < 2 * (resolution + 1); ++i) {
		vertices[5 * i] = vertices[5 * (i - resolution-1)];
		vertices[5 * i + 1] = vertices[5 * (i - resolution-1) + 1];
		vertices[5 * i + 2] = -0.5;
		vertices[5 * i + 3] = vertices[5 * (i - resolution-1) + 3];
		vertices[5 * i + 4] = vertices[5 * (i - resolution-1) + 4];
	}

	unsigned int* indices = new unsigned int[pointCount]();

	// face 1 
	for (int i = 0; i < resolution - 1; i++) {
		indices[3 * i] = 0;
		indices[3 * i + 1] = i + 1;
		indices[3 * i + 2] = i + 2;
	}
	indices[3 * (resolution - 1)] = 0;
	indices[(3 * (resolution - 1)) + 1] = resolution;
	indices[(3 * (resolution - 1)) + 2] = 1;

	// face 2
	for (int i = resolution; i < 2 * resolution-1; i++) {
		indices[3 * i] = resolution+1;
		indices[3 * i + 1] = i + 2;
		indices[3 * i + 2] = i + 3;
	}

	indices[3 * 2 * (resolution - 1)+3] = resolution+1;
	indices[(3 * 2 * (resolution - 1)) + 4] = 2*resolution+1;
	indices[(3 * 2 * (resolution - 1)) + 5] = resolution+2;

	// side
	for (int i = 2*resolution; i < 3 * resolution-1; i++) {
		indices[3 * i] = i - 2 * resolution + 1;
		indices[3 * i + 1] = i - 2 * resolution + 1 + resolution + 1;
		indices[3 * i + 2] = i - 2 * resolution + 1 + resolution + 2;
	}
	indices[3 * 3 * (resolution - 1) + 6] = resolution;
	indices[(3 * 3 * (resolution - 1)) + 7] = 2*resolution + 1;
	indices[(3 * 3 * (resolution - 1)) + 8] = resolution + 2;


	for (int i = 3 * resolution; i < 4 * resolution - 1; i++) {
		indices[3 * i] = i - 3 * resolution + 1;
		indices[3 * i + 1] = i - 3 * resolution + 2;
		indices[3 * i + 2] = i - 3 * resolution + 1 + resolution + 2;
	}
	indices[3 * 4 * (resolution - 1) + 9] = resolution;
	indices[(3 * 4 * (resolution - 1)) + 10] = 1;
	indices[(3 * 4 * (resolution - 1)) + 11] = resolution + 2;



	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pointCount, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	delete[] vertices;
	delete[] indices;
}