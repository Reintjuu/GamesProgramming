#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"

using namespace std;

void keyboardHandler(unsigned char key, int a, int b)
{
	if (key == 27)
		glutExit();
}

const char * fragshader_name = "fragmentshader.fsh";
const char * vertexshader_name = "vertexshader.vsh";

GLuint shaderID;
GLuint vao;
GLuint vbo1, vbo2;
GLuint positionID, colorID;

//const GLfloat vertices[] =
//{
//	0.5, -0.5, 0.0, 1.0,
//	-0.5, -0.5, 0.0, 1.0,
//	-0.5, 0.5, 0.0, 1.0,
//	0.5, 0.5, 0.0, 1.0,
//};

const GLfloat vertices[] =
{
	0.2f, -0.2f, 0.0f, 1.0f,
	0.2f, -0.1f, 0.0f, 1.0f,
	0.4f, 0.0f, 0.0f, 1.0f,
	0.2f, 0.1f, 0.0f, 1.0f,
	0.2f, 0.2f, 0.0f, 1.0f,
	0.1f, 0.2f, 0.0f, 1.0f,
	0.0f, 0.4f, 0.0f, 1.0f,
	-0.1f, 0.2f, 0.0f, 1.0f,
	-0.2f, 0.2f, 0.0f, 1.0f,
	-0.2f, 0.1f, 0.0f, 1.0f,
	-0.4f, 0.0f, 0.0f, 1.0f,
	-0.2f, -0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f, 0.0f, 1.0f,
	-0.1f, -0.2f, 0.0f, 1.0f,
	0.0f, -0.4f, 0.0f, 1.0f,
	0.1f, -0.2f, 0.0f, 1.0f
};


const GLfloat colors[] =
{
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f,
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.0f, 1.0f
};

void Render()
{
	const glm::vec4 blue = glm::vec4(0.0f, 0.0f, 0.4f, 1.0f);
	glClearBufferfv(GL_COLOR, 0, glm::value_ptr(blue));

	glUseProgram(shaderID);

	glBindVertexArray(vao);
	glDrawArrays(GL_LINE_LOOP, 0, 16);
	glBindVertexArray(0);
	glLineWidth(2.0);

	//glDisableVertexAttribArray(positionID);
	//glDisableVertexAttribArray(colorID);

	glutSwapBuffers();
}

int main(int argc, char ** argv)
{
#pragma region << * * * * * * Setup GLut & GLew * * * * * >>

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello OpenGL");
	glutDisplayFunc(Render);
	glutKeyboardFunc(keyboardHandler);

	glewInit();

#pragma endregion

#pragma region << * * * * * * Shader Stuff * * * * * >>
	char * fragshader = glsl::readFile(fragshader_name);
	GLuint fshID = glsl::makeFragmentShader(fragshader);

	char * vertexshader = glsl::readFile(vertexshader_name);
	GLuint vshID = glsl::makeVertexShader(vertexshader);

	shaderID = glsl::makeShaderProgram(vshID, fshID);

#pragma endregion

#pragma region << * * * * * * Buffer Stuff * * * * * >>
	glGenBuffers(1, &vbo1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	positionID = glGetAttribLocation(shaderID, "position");
	colorID = glGetAttribLocation(shaderID, "color");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glVertexAttribPointer(positionID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(positionID);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colorID);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
#pragma endregion

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	glutMainLoop();

	return 0;
}