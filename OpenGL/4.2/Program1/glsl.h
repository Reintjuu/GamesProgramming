#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <fstream>

using namespace std;

class glsl
{
private:
	static char* contents;
public:
	glsl();
	~glsl();
	static char* readFile(const char* filename);
	static bool compiledStatus(GLint shaderID);
	static GLuint makeVertexShader(const char* shaderSource);
	static GLuint makeFragmentShader(const char* shaderSource);
	static GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
};

