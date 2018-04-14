#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "Entity.h"
#include "Camera.h"

using namespace std;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const char * fragshader_name = "fragmentshader.fsh";
const char * vertexshader_name = "vertexshader.vsh";
const int WIDTH = 800, HEIGHT = 600;
const int CENTER_X = WIDTH / 2, CENTER_Y = HEIGHT / 2;
const int DELTA = 10;

//--------------------------------------------------------------------------------
// Typedefs
//--------------------------------------------------------------------------------
struct LightSource
{
	glm::vec3 position;
};

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

GLuint shaderID;
GLuint uniform_mv;
GLuint uniform_proj;
GLuint uniform_apply_texture;
GLuint uniform_material_ambient;
GLuint uniform_material_diffuse;
GLuint uniform_material_specular;
GLuint uniform_material_power;

glm::mat4 view, projection;

LightSource light;

Entity entities[2];

// Camera.
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
int currentZoom = 0;

// Timing.
float deltaTime = 0.0f;	// Time between current frame and last frame.
float lastFrame = 0.0f;

//--------------------------------------------------------------------------------
// Keyboard/Mouse handling
//--------------------------------------------------------------------------------

void OnKeyDown()
{
	if (GetAsyncKeyState(VK_ESCAPE))
		glutExit();

	if (GetAsyncKeyState(0x57)) // W.
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (GetAsyncKeyState(0x53)) // S.
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (GetAsyncKeyState(0x41)) // A.
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (GetAsyncKeyState(0x44)) // D.
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void OnMouseMove(int x, int y)
{
	camera.ProcessMouseMovement(x - CENTER_X, CENTER_Y - y);
	
	// If not already, warp the cursor to the center.
	if (x != CENTER_X || y != CENTER_Y)
	{
		glutWarpPointer(CENTER_X, CENTER_Y);
	}
}

void OnScroll(int button, int direction, int x, int y)
{
	camera.ProcessMouseScroll(direction);
}

//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
	const float currentFrame = glutGet(GLUT_ELAPSED_TIME) / 100.0f;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	OnKeyDown();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	view = camera.GetViewMatrix();

	projection = glm::perspective(glm::radians(camera.Zoom), float(WIDTH) / HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));

	entities[0].Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
	entities[1].Rotate(0.05f, glm::vec3(1.0f, 0.0f, 0.5f));

	glUseProgram(shaderID);

	for (auto& entity : entities)
	{
		if (entity.apply_texture)
		{
			glUniform1i(uniform_apply_texture, 1);
			glBindTexture(GL_TEXTURE_2D, entity.textureID);
		}
		else
			glUniform1i(uniform_apply_texture, 0);

		glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(entity.mv));
		glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(entity.material.ambientColor));
		glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(entity.material.diffuseColor));
		glUniform3fv(uniform_material_specular, 1, glm::value_ptr(entity.material.specular));
		glUniform1f(uniform_material_power, entity.material.power);

		glBindVertexArray(entity.vao);
		glDrawArrays(GL_TRIANGLES, 0, entity.mesh.vertices.size());
		glBindVertexArray(0);
	}

	glutSwapBuffers();
}

// Render method that is called by the timer function.
void Render(int n)
{
	Render();
	glutTimerFunc(DELTA, Render, 0);
}

void InitGlutGlew(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Final Assignment - Reinier de Vries");

	glutMotionFunc(OnMouseMove);
	glutPassiveMotionFunc(OnMouseMove);
	glutMouseWheelFunc(OnScroll);

	glutDisplayFunc(Render);
	glutTimerFunc(DELTA, Render, 0);

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glewInit();
}

void InitShaders()
{
	char * fragshader = glsl::readFile(fragshader_name);
	GLuint fshID = glsl::makeFragmentShader(fragshader);

	char * vertexshader = glsl::readFile(vertexshader_name);
	GLuint vshID = glsl::makeVertexShader(vertexshader);

	shaderID = glsl::makeShaderProgram(vshID, fshID);
}

void InitMatrices()
{
	view = glm::lookAt(
		glm::vec3(0.0, 2.0, 6.0),
		glm::vec3(1.5, 0.5, 0.0),
		glm::vec3(0.0, 1.0, 0.0));

	projection = glm::perspective(
		glm::radians(45.0f),
		1.0f * WIDTH / HEIGHT, 0.1f,
		20.0f);
}

void InitBuffers()
{
	GLuint vbo_vertices, vbo_normals, vbo_uvs;

	const GLuint positionID = glGetAttribLocation(shaderID, "position");
	const GLuint normalID = glGetAttribLocation(shaderID, "normal");
	const GLuint uvID = glGetAttribLocation(shaderID, "uv");

	// Attach to program (needed to send uniform vars)
	glUseProgram(shaderID);

	// Make uniform vars
	uniform_mv = glGetUniformLocation(shaderID, "mv");
	uniform_proj = glGetUniformLocation(shaderID, "projection");
	GLuint uniform_light_pos = glGetUniformLocation(shaderID, "lightPos");
	uniform_apply_texture = glGetUniformLocation(shaderID, "applyTexture");
	uniform_material_ambient = glGetUniformLocation(shaderID, "matAmbient");
	uniform_material_diffuse = glGetUniformLocation(shaderID, "matDiffuse");
	uniform_material_specular = glGetUniformLocation(shaderID, "matSpecular");
	uniform_material_power = glGetUniformLocation(shaderID, "matPower");

	// Fill uniform vars
	glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
	glUniform3fv(uniform_light_pos, 1, glm::value_ptr(light.position));

	for (auto& entity : entities)
	{
		// vbo for vertices
		glGenBuffers(1, &vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, entity.mesh.vertices.size() * sizeof(glm::vec3),
			&entity.mesh.vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// vbo for normals
		glGenBuffers(1, &vbo_normals);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glBufferData(GL_ARRAY_BUFFER, entity.mesh.normals.size() * sizeof(glm::vec3),
			&entity.mesh.normals[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// vbo for uvs
		glGenBuffers(1, &vbo_uvs);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glBufferData(GL_ARRAY_BUFFER, entity.mesh.uvs.size() * sizeof(glm::vec2),
			&entity.mesh.uvs[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &(entity.vao));
		glBindVertexArray(entity.vao);

		// Bind vertices to vao
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(positionID);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
		glVertexAttribPointer(normalID, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(normalID);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
		glVertexAttribPointer(uvID, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(uvID);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
}


void CreateEntities()
{
	entities[0] = Entity(&view);
	entities[0].LoadObject("Objects/teapot.obj", "Textures/Yellobrk.bmp");
	entities[0].material = Material(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0), 128);

	entities[1] = Entity(&view);
	entities[1].LoadObject("Objects/box.obj", "Textures/uvtemplate.bmp");
	entities[1].material = Material(glm::vec3(0.3, 0.3, 0.0), glm::vec3(0.5, 0.5, 0.0), glm::vec3(1.0), 128);
	entities[1].Transform(glm::translate(glm::mat4(), glm::vec3(3.0, 0.5, 0.0)));
}


int main(int argc, char ** argv)
{
	InitGlutGlew(argc, argv);
	InitShaders();

	CreateEntities();
	InitMatrices();

	light.position = glm::vec3(4.0, 4.0, 4.0);

	InitBuffers();

	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	glutMainLoop();

	return 0;
}
