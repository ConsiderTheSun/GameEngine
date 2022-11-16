#include "SphereMesh.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

#include <glm/glm/glm.hpp>

SphereMesh::SphereMesh(int resolution) :pointCount(3* resolution * (2 * (resolution - 2) + 2)) {

	glGenVertexArrays(1, &VAO);

	GLuint EBO;

	// creates the array for the vertices of the triangles
	const int VERT_SIZE = 8;
	const int VERT_COUNT = VERT_SIZE * (resolution * (resolution - 1) + 2);
	float* vertices = new float[VERT_COUNT]();


	// makes the verts at the poles
	const int TOP_INDEX = resolution * (resolution - 1);
	const int BOTTOM_INDEX = resolution * (resolution - 1)+1;

	vertices[VERT_SIZE * TOP_INDEX] = 0;
	vertices[VERT_SIZE * TOP_INDEX + 1] = 0.5;
	vertices[VERT_SIZE * TOP_INDEX + 2] = 0;

	vertices[VERT_SIZE * TOP_INDEX + 3] = 0;
	vertices[VERT_SIZE * TOP_INDEX + 4] = 0;

	vertices[VERT_SIZE * TOP_INDEX + 5] = 0;
	vertices[VERT_SIZE * TOP_INDEX + 6] = 1;
	vertices[VERT_SIZE * TOP_INDEX + 7] = 0;

	vertices[VERT_SIZE * BOTTOM_INDEX] = 0;
	vertices[VERT_SIZE * BOTTOM_INDEX + 1] = -0.5;
	vertices[VERT_SIZE * BOTTOM_INDEX + 2] = 0;

	vertices[VERT_SIZE * BOTTOM_INDEX + 3] = 0;
	vertices[VERT_SIZE * BOTTOM_INDEX + 4] = 0;

	vertices[VERT_SIZE * BOTTOM_INDEX + 5] = 0;
	vertices[VERT_SIZE * BOTTOM_INDEX + 6] = -1;
	vertices[VERT_SIZE * BOTTOM_INDEX + 7] = 0;

	float theta, phi;
	float deltaTheta = M_PI / resolution;
	float deltaPhi = 2 * M_PI / resolution;

	const int STRIP_SIZE = resolution - 1;
	glm::vec3 direction;
	for (int currentStrip = 0; currentStrip < resolution; ++currentStrip) {

		phi = currentStrip * deltaPhi;

		for (int i = 0; i < STRIP_SIZE; ++i) {

			theta = -M_PI + deltaTheta * (i+1);

			int currentIndex = VERT_SIZE * (STRIP_SIZE * currentStrip + i);

			// finds the direction on the unit sphere at theta, phi
			direction.x = sin(theta) * cos(phi);
			direction.y = cos(theta);
			direction.z = sin(theta) * sin(phi);

			direction = glm::normalize(direction);

			vertices[currentIndex] = 0.5 * direction.x;
			vertices[currentIndex+1] = 0.5 * direction.y;
			vertices[currentIndex+2] = 0.5 * direction.z;

			vertices[currentIndex + 5] = direction.x;
			vertices[currentIndex + 6] = direction.y;
			vertices[currentIndex + 7] = direction.z;
		}
	}


	// creates the array for the indices of the triangle vertices
	unsigned int* indices = new unsigned int[pointCount]();

	const int STRIP_TRI_COUNT = 2 * (resolution - 2) + 2;
	int stripOffset, triIndex;
	for (int currentStrip = 0; currentStrip < resolution-1; ++currentStrip) {

		stripOffset = STRIP_TRI_COUNT * currentStrip;

		// bottom triangle
		triIndex = 3 * stripOffset;

		indices[triIndex] = BOTTOM_INDEX;
		indices[triIndex +1] = STRIP_SIZE * currentStrip;
		indices[triIndex +2] = STRIP_SIZE * (currentStrip+1);

		for (int i = 1; i < resolution - 1; ++i) {
			triIndex = 3 * (stripOffset+i);

			indices[triIndex] = STRIP_SIZE * currentStrip + i-1;
			indices[triIndex +1] = STRIP_SIZE * (currentStrip+1) + i-1;
			indices[triIndex +2] = STRIP_SIZE * currentStrip + i;
		}

		for (int i = 1; i < resolution - 1; ++i) {
			triIndex = 3 * (stripOffset + i + resolution - 2);

			indices[triIndex] = STRIP_SIZE * (currentStrip + 1) + i - 1;
			indices[triIndex + 1] = STRIP_SIZE * (currentStrip + 1) + i;
			indices[triIndex + 2] = STRIP_SIZE * currentStrip + i;
		}

		// top triangle
		triIndex = 3 * (stripOffset + STRIP_TRI_COUNT - 1);

		indices[triIndex] = TOP_INDEX;
		indices[triIndex+1] = STRIP_SIZE * (currentStrip + 1) + resolution - 2;
		indices[triIndex+2] = STRIP_SIZE * currentStrip + resolution - 2;
	}


	stripOffset = STRIP_TRI_COUNT * (resolution-1);


	// bottom triangle
	triIndex = 3 * stripOffset;

	indices[triIndex] = BOTTOM_INDEX;
	indices[triIndex + 1] = STRIP_SIZE * (resolution - 1);
	indices[triIndex + 2] = STRIP_SIZE * 0;

	for (int i = 1; i < resolution - 1; ++i) {
		triIndex = 3 * (stripOffset + i);

		indices[triIndex] = STRIP_SIZE * (resolution - 1) + i - 1;
		indices[triIndex + 1] = STRIP_SIZE * 0 + i - 1;
		indices[triIndex + 2] = STRIP_SIZE * (resolution - 1) + i;
	}

	for (int i = 1; i < resolution - 1; ++i) {
		triIndex = 3 * (stripOffset + i + resolution - 2);

		indices[triIndex] = STRIP_SIZE * 0 + i - 1;
		indices[triIndex + 1] = STRIP_SIZE * 0 + i;
		indices[triIndex + 2] = STRIP_SIZE * (resolution - 1) + i;
	}

	// top triangle
	triIndex = 3 * (stripOffset + STRIP_TRI_COUNT - 1);

	indices[triIndex] = TOP_INDEX;
	indices[triIndex + 1] = STRIP_SIZE * 0 + resolution - 2;
	indices[triIndex + 2] = STRIP_SIZE * (resolution - 1) + resolution - 2;


	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * VERT_COUNT, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pointCount, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERT_SIZE * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VERT_SIZE * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERT_SIZE * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	
	delete[] vertices;
	delete[] indices;
}
