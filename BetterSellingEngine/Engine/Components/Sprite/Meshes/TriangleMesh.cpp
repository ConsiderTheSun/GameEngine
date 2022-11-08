#include "TriangleMesh.h"


#include <iostream>


TriangleMesh::TriangleMesh(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint, 
						   glm::vec2 firstTex, glm::vec2 secondTex, glm::vec2 thirdTex){
	

	glGenVertexArrays(1, &VAO);
	GLuint EBO;

	float vertices[15] = {
		//positions            //tex coords
		firstPoint.x,  firstPoint.y,  firstPoint.z, firstTex.x, firstTex.y,  // lower-left corner
		secondPoint.x,  secondPoint.y,  secondPoint.z, secondTex.x, secondTex.y,  // lower-right corner
		thirdPoint.x,  thirdPoint.y,  thirdPoint.z, thirdTex.x, thirdTex.y  // top-center corner
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}