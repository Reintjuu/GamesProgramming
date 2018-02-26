#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "main.h"
#include "glsl.h"

using namespace std;

const char* fragmentshader_name = "fragmentshader.fsh";
const char* vertexshader_name = "vertexshader.vsh";

GLuint shaderID;

void keyboardHandler(unsigned char key, int a, int b)
{
	if (key == 27)
	{
		glutExit();
	}
}

void Render()
{
	// Drawing a quad.
	glBegin(GL_QUADS);

	// Right top.
	glColor3f(0, 0, 1.0);
	glVertex2f(.5, .5);

	// Left top.
	glColor3f(0, 1.0, 0);
	glVertex2f(-.5, .5);

	// Left bottom.
	glColor3f(1.0, 1.0, 0);
	glVertex2f(-.5, -.5);

	// Right bottom.
	glColor3f(1.0, 0, 0);
	glVertex2f(.5, -.5);

	glEnd();

	// Shaders
	glUseProgram(shaderID);
	glPointSize(40.0f);
	glDrawArrays(GL_POINTS, 0, 1);



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
	char *fragshader = glsl::readFile(fragmentshader_name);
	GLuint fshID = glsl::makeFragmentShader(fragshader);
	char *vertexshader = glsl::readFile(vertexshader_name);
	GLuint vshID = glsl::makeVertexShader(vertexshader);

	shaderID = glsl::makeShaderProgram(vshID, fshID);
#pragma endregion

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	glutMainLoop();

	return 0;
}