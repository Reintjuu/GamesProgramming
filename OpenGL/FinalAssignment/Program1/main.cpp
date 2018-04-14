#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.hpp"
#include "texture.hpp"


using namespace std;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const char * fragshader_name = "fragmentshader.fsh";
const char * vertexshader_name = "vertexshader.vsh";
const int WIDTH = 800, HEIGHT = 600;
const int DELTA = 10;


//--------------------------------------------------------------------------------
// Typedefs
//--------------------------------------------------------------------------------
struct LightSource
{
    glm::vec3 position;
};

struct Material
{
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specular;
    float power;
};

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

GLuint shaderID;
GLuint vao[2];

GLuint uniform_mv;
GLuint uniform_apply_texture;
GLuint uniform_material_ambient;
GLuint uniform_material_diffuse;
GLuint uniform_material_specular;
GLuint uniform_material_power;

GLuint textureID[2];

glm::mat4 model[2], view, projection;
glm::mat4 mv[2];

LightSource light;
Material material[2];
bool apply_texture[2];


//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------


vector<glm::vec3> vertices[2];
vector<glm::vec3> normals[2];
vector<glm::vec2> uvs[2];


//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model[0] = glm::rotate(model[0], 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
    model[1] = glm::rotate(model[1], 0.05f, glm::vec3(1.0f, 0.0f, 0.5f));

    glUseProgram(shaderID);

    for (int i = 0; i < 2; i++)
    {
        mv[i] = view * model[i];

        if (apply_texture[i])
        {
            glUniform1i(uniform_apply_texture, 1);
            glBindTexture(GL_TEXTURE_2D, textureID[i]);
        }
        else
            glUniform1i(uniform_apply_texture, 0);

        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv[i]));
        glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(material[i].ambientColor));
        glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(material[i].diffuseColor));
        glUniform3fv(uniform_material_specular, 1, glm::value_ptr(material[i].specular));
        glUniform1f(uniform_material_power, material[i].power);

        glBindVertexArray(vao[i]);
        glDrawArrays(GL_TRIANGLES, 0, vertices[i].size());
        glBindVertexArray(0);
    }

    glutSwapBuffers();
}



//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA, Render, 0);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(DELTA, Render, 0);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    glewInit();
}


//------------------------------------------------------------
// void InitShaders()
// Initialized the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders()
{
    char * fragshader = glsl::readFile(fragshader_name);
    GLuint fshID = glsl::makeFragmentShader(fragshader);

    char * vertexshader = glsl::readFile(vertexshader_name);
    GLuint vshID = glsl::makeVertexShader(vertexshader);

    shaderID = glsl::makeShaderProgram(vshID, fshID);
}


//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices()
{
    model[0] = glm::mat4();
    model[1] = glm::translate(glm::mat4(), glm::vec3(3.0, 0.5, 0.0));;

    view = glm::lookAt(
        glm::vec3(0.0, 2.0, 6.0),
        glm::vec3(1.5, 0.5, 0.0),
        glm::vec3(0.0, 1.0, 0.0));
    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        20.0f);

    mv[0] = view * model[0];
    mv[1] = view * model[1];
}

//------------------------------------------------------------
// void InitObjects()
//------------------------------------------------------------

void InitObjects()
{
    bool res = loadOBJ("Objects/teapot.obj", vertices[0], uvs[0], normals[0]);
    res = loadOBJ("Objects/box.obj", vertices[1], uvs[1], normals[1]);

    textureID[0] = loadBMP("Textures/Yellobrk.bmp");
    textureID[1] = loadBMP("Textures/uvtemplate.bmp");
}


//------------------------------------------------------------
// void InitMaterialsLight()
//------------------------------------------------------------

void InitMaterialsLight()
{
    light.position = glm::vec3(4.0, 4.0, 4.0);
    material[0].ambientColor = glm::vec3(0.0, 0.0, 0.0);
    material[0].diffuseColor = glm::vec3(0.0, 0.0, 0.0);
    material[0].specular = glm::vec3(1.0);
    material[0].power = 128;
    apply_texture[0] = true;

    material[1].ambientColor = glm::vec3(0.3, 0.3, 0.0);
    material[1].diffuseColor = glm::vec3(0.5, 0.5, 0.0);
    material[1].specular = glm::vec3(1.0);
    material[1].power = 128;
    apply_texture[1] = false;
}


//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
    GLuint vbo_vertices, vbo_normals, vbo_uvs;

    GLuint positionID = glGetAttribLocation(shaderID, "position");
    GLuint normalID = glGetAttribLocation(shaderID, "normal");
    GLuint uvID = glGetAttribLocation(shaderID, "uv");

    // Attach to program (needed to send uniform vars)
    glUseProgram(shaderID);

    // Make uniform vars
    uniform_mv = glGetUniformLocation(shaderID, "mv");
    GLuint uniform_proj = glGetUniformLocation(shaderID, "projection");
    GLuint uniform_light_pos = glGetUniformLocation(shaderID, "lightPos");
    uniform_apply_texture = glGetUniformLocation(shaderID, "applyTexture");
    uniform_material_ambient = glGetUniformLocation(shaderID, "matAmbient");
    uniform_material_diffuse = glGetUniformLocation(shaderID, "matDiffuse");
    uniform_material_specular = glGetUniformLocation(shaderID, "matSpecular");
    uniform_material_power = glGetUniformLocation(shaderID, "matPower");

    // Fill uniform vars
    glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(uniform_light_pos, 1, glm::value_ptr(light.position));

    for (int i = 0; i < 2; i++)
    {

        // vbo for vertices
        glGenBuffers(1, &vbo_vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glBufferData(GL_ARRAY_BUFFER, vertices[i].size() * sizeof(glm::vec3),
            &vertices[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // vbo for normals
        glGenBuffers(1, &vbo_normals);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
        glBufferData(GL_ARRAY_BUFFER, normals[i].size() * sizeof(glm::vec3),
            &normals[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // vbo for uvs
        glGenBuffers(1, &vbo_uvs);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
        glBufferData(GL_ARRAY_BUFFER, uvs[i].size() * sizeof(glm::vec2),
            &uvs[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &(vao[i]));
        glBindVertexArray(vao[i]);

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


int main(int argc, char ** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitMatrices();
    InitObjects();
    InitMaterialsLight();
    InitBuffers();

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    glutMainLoop();

    return 0;
}
