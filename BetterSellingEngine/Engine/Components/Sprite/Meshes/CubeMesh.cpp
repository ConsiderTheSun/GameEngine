#include "CubeMesh.h"


#include <iostream>
GLuint CubeMesh::cubeVAO = -1;

CubeMesh::CubeMesh(float sizeLength){

    if (cubeVAO == -1) {
        glGenVertexArrays(1, &cubeVAO);
    }
	GLuint VBO;
	GLuint EBO;

	float p = 0.5f * sizeLength;

    float vertices[] = {
        
        -p, -p, -p,  0.0f, 0.0f,
         p, -p, -p,  1.0f, 0.0f,
         p,  p, -p,  1.0f, 1.0f,
        -p,  p, -p,  0.0f, 1.0f,

        -p, -p,  p,  0.0f, 0.0f,
         p, -p,  p,  1.0f, 0.0f,
         p,  p,  p,  1.0f, 1.0f,
        -p,  p,  p,  0.0f, 1.0f,

        -p,  p,  p,  1.0f, 0.0f,
        -p,  p, -p,  1.0f, 1.0f,
        -p, -p, -p,  0.0f, 1.0f,
        -p, -p,  p,  0.0f, 0.0f,

         p,  p,  p,  1.0f, 0.0f,
         p,  p, -p,  1.0f, 1.0f,
         p, -p, -p,  0.0f, 1.0f,
         p, -p,  p,  0.0f, 0.0f,

        -p, -p, -p,  0.0f, 1.0f,
         p, -p, -p,  1.0f, 1.0f,
         p, -p,  p,  1.0f, 0.0f,
        -p, -p,  p,  0.0f, 0.0f,

        -p,  p, -p,  0.0f, 1.0f,
         p,  p, -p,  1.0f, 1.0f,
         p,  p,  p,  1.0f, 0.0f,
        -p,  p,  p,  0.0f, 0.0f
    };


	unsigned int indices[] = {
	   0, 1, 2,
       2, 3, 0,

       4, 5, 6,
       6, 7, 4,

       8, 9, 10,
       10, 11, 8,

       12, 13, 14,
       14, 15, 12,

       16, 17, 18,
       18, 19, 16,

       20, 21, 22,
       22, 23, 20
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(cubeVAO);
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