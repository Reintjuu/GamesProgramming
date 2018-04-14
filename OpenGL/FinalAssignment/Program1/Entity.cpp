#include "Entity.h"
#include "objloader.hpp"
#include "texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(glm::mat4 * view)
{
	this->view = view;
	this->Transform(glm::mat4());
}

Entity::Entity(): view(nullptr)
{
}

Entity::~Entity()
{
}

void Entity::Transform(const glm::mat4& transformation)
{
	model = transformation;
	mv = *view * model;
}

void Entity::LoadObject(const char * object, const char * texture)
{
	loadOBJ(object, mesh.vertices, mesh.uvs, mesh.normals);

	if (texture != nullptr)
	{
		textureID = loadBMP(texture);
		apply_texture = true;
	}
}

void Entity::Rotate(const float angle, const glm::vec3& axis)
{
	Transform(glm::rotate(model, angle, axis));
}
