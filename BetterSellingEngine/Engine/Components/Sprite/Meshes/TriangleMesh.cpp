#include "TriangleMesh.h"

#include <glm/glm/geometric.hpp>
#include <iostream>


TriangleMesh::TriangleMesh(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint, 
						   glm::vec2 firstTex, glm::vec2 secondTex, glm::vec2 thirdTex){
	

	glGenVertexArrays(1, &VAO);
	GLuint EBO;

	glm::vec3 p1 = glm::vec3(firstPoint.x, firstPoint.y, firstPoint.z);
	glm::vec3 p2 = glm::vec3(secondPoint.x, secondPoint.y, secondPoint.z);
	glm::vec3 p3 = glm::vec3(thirdPoint.x, thirdPoint.y, thirdPoint.z);
	glm::vec3 normal = glm::normalize(glm::cross(p2 - p1, p3 - p1));

	float vertices[24] = {
		//positions            //tex coords
		p1.x,  p1.y,  p1.z, firstTex.x, firstTex.y, normal.x, normal.y, normal.z,  // lower-left corner
		p2.x,  p2.y,  p2.z, secondTex.x, secondTex.y, normal.x, normal.y, normal.z, // lower-right corner
		p3.x,  p3.y,  p3.z, thirdTex.x, thirdTex.y, normal.x, normal.y, normal.z,  // top-center corner
	};

	unsigned int indices[] = {
			0, 1, 2,   // Triangle
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}