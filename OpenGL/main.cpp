#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>   
#include <time.h>
#include "ShaderLoader.h"

float r = 1.0;
float b = 1.0;
float g = 1.0;


//GLOBAL Verts

GLuint hexpro = NULL;
GLuint quadpro = NULL;
GLuint Hex = NULL;
GLuint Quad = NULL;
GLuint hexVAO;
GLuint hexVBO;
GLuint hexEBO;
GLuint quadVAO;
GLuint quadVBO;
GLuint quadEBO;
GLuint texture;
GLuint texture1;
float currentTime;

/*

Hexagon colors:

1.0f, 1.0f, 1.0f - middle
1.0f, 0.0f, 0.0f - bottom right
1.0f, 0.4f, 0.0f - bottom left
1.0f, 1.0f, 0.0f - left
0.0f, 1.0f, 0.0f - top left
0.0f, 0.0f, 1.0f - top right
1.0f, 0.0f, 1.0f - right

using 4 trinagles
*/


GLuint hexIndices[] = {
	0, 1, 2,
	2, 3, 4,
	4, 5, 0,
	0, 2, 4,
};

GLfloat hexVerts[] = {
	0.7f, -0.9f, 0.0f,	1.0f, 0.0f, 0.0f, //bottom right	0
	0.85f, -0.7f, 0.0f,	1.0f, 0.0f, 1.0f, //right			1
	0.7f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f, //top right		2
	0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, //top left		3
	0.35f, -0.7f, 0.0f,	1.0f, 1.0f, 0.0f, //left			4
	0.5f, -0.9f, 0.0f,	1.0f, 0.4f, 0.0f, //bottom left		5
};

GLuint quadIndices[] = {
	0, 1, 2,
	2, 3, 0,
};

GLfloat quadVerts[] = {
	0.95f, 0.95f, 0.0f,		1.0f, 0.0f, 0.0f,	1.0f, 0.0f,		//top right		0
	-0.95f, 0.95f, 0.0f,	1.0f, 0.0f, 1.0f,	0.0f, 0.0f,		//top left		1
	-0.95f, -0.95f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,		//bottom left	2
	0.95f, -0.95f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		//bottom right	3
};


void Render() {
	glClear(GL_COLOR_BUFFER_BIT);
	
	r = (rand() % 10 + 1)/10.0f;
	g = (rand() % 10 + 1)/10.0f;
	b = (rand() % 10 + 1)/10.0f;
	glClearColor(r, g, b, 1.0);

	glUseProgram(quadpro);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(quadpro, "tex"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(quadpro, "tex1"), 1);
	GLint currentTimeLoc1 = glGetUniformLocation(hexpro, "currentTime");
	glUniform1f(currentTimeLoc1, currentTime);
	glBindVertexArray(quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
	
	glUseProgram(hexpro);
	GLint currentTimeLoc = glGetUniformLocation(hexpro, "currentTime");
	glUniform1f(currentTimeLoc, currentTime);
	glBindVertexArray(hexVAO);
	glRotatef(90, 0, 1, 0);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	glutSwapBuffers();
}

void Update() {
	currentTime = (float) glutGet(GLUT_ELAPSED_TIME);
	currentTime = currentTime * 0.001f;
	glutPostRedisplay();
}

int main(int argc, char **argv) {
	srand((unsigned int)time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Summ 1 ~ Henry Oliver");

	if (glewInit() != GLEW_OK) {

		std::cout << "Glew INIT FAILED";
		system("pause");
	}

	glClearColor(1.0, 0.0, 0.0, 1.0);

	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image = SOIL_load_image("Resources/FRAME1.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	unsigned char* image2 = SOIL_load_image("Resources/FRAME2.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SOIL_free_image_data(image2);
	glBindTexture(GL_TEXTURE_2D, 1);



	hexpro = ShaderLoader::CreateProgram("Resources/hex.vs", "Resources/hex.fs");
	quadpro = ShaderLoader::CreateProgram("Resources/quad.vs", "Resources/quad.fs");

	glGenVertexArrays(1, &hexVAO);
	glBindVertexArray(hexVAO);

	glGenBuffers(1, &hexEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexIndices), hexIndices, GL_STATIC_DRAW);
	
	glGenBuffers(1, &hexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, hexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(hexVerts), hexVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);



	glGenVertexArrays(1, &quadVAO);
	glBindVertexArray(quadVAO);

	glGenBuffers(1, &quadEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);

	glGenBuffers(1, &quadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glutDisplayFunc(Render);

	glutIdleFunc(Update);

	glutMainLoop();

	return 0;
}