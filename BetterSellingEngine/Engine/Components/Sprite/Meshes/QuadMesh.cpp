#include "QuadMesh.h"


#include <iostream>
GLuint QuadMesh::quadVAO = -1;
QuadMesh::QuadMesh(glm::vec3 firstPoint, glm::vec3 secondPoint, glm::vec3 thirdPoint, glm::vec3 fourthPoint,
						   glm::vec2 firstTex, glm::vec2 secondTex, glm::vec2 thirdTex, glm::vec2 fourthTex){
	if (quadVAO == -1) {
		glGenVertexArrays(1, &quadVAO);
	}

	
	GLuint VBO;
	GLuint EBO;

	float vertices[20] = {
		//positions            //tex coords
		firstPoint.x,  firstPoint.y,  firstPoint.z, firstTex.x, firstTex.y,  // top right
		secondPoint.x,  secondPoint.y,  secondPoint.z, secondTex.x, secondTex.y,  // bottom right
		thirdPoint.x,  thirdPoint.y,  thirdPoint.z, thirdTex.x, thirdTex.y,  // bottom left
		fourthPoint.x,  fourthPoint.y,  fourthPoint.z, fourthTex.x, fourthTex.y  // top left 
	};

	unsigned int indices[] = {
	   0, 1, 3, // first triangle
	   1, 2, 3  // second triangle
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(quadVAO);

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