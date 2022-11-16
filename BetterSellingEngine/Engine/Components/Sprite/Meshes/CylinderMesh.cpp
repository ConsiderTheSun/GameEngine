#include "CylinderMesh.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

#include <glm/glm/glm.hpp>

CylinderMesh::CylinderMesh(int resolution) :pointCount(3 * 4* resolution) {

	glGenVertexArrays(1, &VAO);

	GLuint EBO;

	int vertCount = 4 * (resolution + 1) * 8;
	float* vertices = new float[vertCount]();
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0.5;
	vertices[3] = 0.5;
	vertices[4] = 0.5;
	vertices[5] = 0;
	vertices[6] = 0;
	vertices[7] = 1;


	float deltaTheta = 2 * M_PI / resolution;
	float theta = 0;

	//face 1
	for (int i = 1; i < resolution + 1; ++i) {
		vertices[8 * i] = 0.5f * cos(theta);
		vertices[8 * i + 1] = 0.5 * sin(theta);
		vertices[8 * i + 2] = 0.5;

		vertices[8 * i + 3] = 0.5f * cos(theta) + 0.5;
		vertices[8 * i + 4] = 0.5 * sin(theta) + 0.5;

		vertices[8 * i + 5] = 0;
		vertices[8 * i + 6] = 0;
		vertices[8 * i + 7] = 1;


		vertices[8 * (2 * (resolution + 1) + i)] = vertices[8 * i];
		vertices[8 * (2 * (resolution + 1) + i)+1] = vertices[8 * i+1];
		vertices[8 * (2 * (resolution + 1) + i) + 2] = vertices[8 * i + 2];

		vertices[8 * (2 * (resolution + 1) + i) + 3] = vertices[8 * i + 3];
		vertices[8 * (2 * (resolution + 1) + i) + 4] = vertices[8 * i + 4];

		glm::vec3 n = glm::normalize(glm::vec3(vertices[8 * i], vertices[8 * i + 1], 0));
		vertices[8 * (2 * (resolution + 1) + i) + 5] = n.x;
		vertices[8 * (2 * (resolution + 1) + i) + 6] = n.y;
		vertices[8 * (2 * (resolution + 1) + i) + 7] = 0;

		theta += deltaTheta;
	}

	// face 2
	for (int i = resolution+1; i < 2 * (resolution + 1); ++i) {
		vertices[8 * i] = vertices[8 * (i - resolution-1)];
		vertices[8 * i + 1] = vertices[8 * (i - resolution-1) + 1];
		vertices[8 * i + 2] = -0.5;

		vertices[8 * i + 3] = -vertices[8 * (i - resolution-1) + 3];
		vertices[8 * i + 4] = vertices[8 * (i - resolution-1) + 4];

		vertices[8 * i + 5] = 0;
		vertices[8 * i + 6] = 0;
		vertices[8 * i + 7] = -1;


		vertices[8 * (2 * (resolution + 1) + i)] = vertices[8 * i];
		vertices[8 * (2 * (resolution + 1) + i) + 1] = vertices[8 * i + 1];
		vertices[8 * (2 * (resolution + 1) + i) + 2] = vertices[8 * i + 2];

		vertices[8 * (2 * (resolution + 1) + i) + 3] = vertices[8 * i + 3];
		vertices[8 * (2 * (resolution + 1) + i) + 4] = vertices[8 * i + 4];

		glm::vec3 n = glm::normalize(glm::vec3(vertices[8 * i], vertices[8 * i + 1], 0));
		vertices[8 * (2 * (resolution + 1) + i) + 5] = n.x;
		vertices[8 * (2 * (resolution + 1) + i) + 6] = n.y;
		vertices[8 * (2 * (resolution + 1) + i) + 7] = 0;
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
		indices[3 * i] = i - 2 * resolution + 1 + (2 * (resolution + 1));
		indices[3 * i + 1] = i - 2 * resolution + 1 + resolution + 1 + (2 * (resolution + 1));
		indices[3 * i + 2] = i - 2 * resolution + 1 + resolution + 2 + (2 * (resolution + 1));
	}
	indices[3 * 3 * (resolution - 1) + 6] = resolution + (2 * (resolution + 1));
	indices[(3 * 3 * (resolution - 1)) + 7] = 2*resolution + 1 + (2 * (resolution + 1));
	indices[(3 * 3 * (resolution - 1)) + 8] = resolution + 2 + (2 * (resolution + 1));


	for (int i = 3 * resolution; i < 4 * resolution - 1; i++) {
		indices[3 * i] = i - 3 * resolution + 1 + (2 * (resolution + 1));
		indices[3 * i + 1] = i - 3 * resolution + 2 + (2 * (resolution + 1));
		indices[3 * i + 2] = i - 3 * resolution + 1 + resolution + 2 + (2 * (resolution + 1));
	}
	indices[3 * 4 * (resolution - 1) + 9] = resolution + (2 * (resolution + 1));
	indices[(3 * 4 * (resolution - 1)) + 10] = 1 + (2 * (resolution + 1));
	indices[(3 * 4 * (resolution - 1)) + 11] = resolution + 2 + (2 * (resolution + 1));



	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertCount, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * pointCount, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	delete[] vertices;
	delete[] indices;
}