#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

using namespace std;

struct Material
{
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specular;
	float power;

	Material()
	{
	}

	Material(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specular, float power)
	{
		this->ambientColor = ambientColor;
		this->diffuseColor = diffuseColor;
		this->specular = specular;
		this->power = power;
	}
};

struct Mesh
{
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;

	Mesh()
	{
	}

	Mesh(vector<glm::vec3> vertices, vector<glm::vec3> normals,	vector<glm::vec2> uvs)
	{
		this->vertices = vertices;
		this->normals = normals;
		this->uvs = uvs;
	}
};

class Entity
{
public:
	GLuint vao;
	GLuint textureID;
	bool apply_texture;

	glm::mat4 mv;
	Material material;
	Mesh mesh;

private:
	glm::mat4 model;
	glm::mat4 * view;

public:
	Entity();
	~Entity();
	Entity(glm::mat4 * view);

	void Transform(const glm::mat4& transformation);
	void LoadObject(const char* object, const char* texture = nullptr);
	void Rotate(const float angle, const glm::vec3& axis);
};
