#include "Entity.h"
#include "objloader.hpp"
#include "texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity()
{
	Transform(glm::mat4());
}

Entity::~Entity()
{
}

void Entity::LoadObject(const char * object, const char * texture)
{
	loadOBJ(object, mesh.vertices, mesh.uvs, mesh.normals);

	if (texture != nullptr)
	{
		textureID = loadBMP(texture);
		applyTexture = true;
	}
}

void Entity::Transform(const glm::mat4& transformation)
{
	model = transformation;
}

void Entity::Translate(const glm::vec3& translation)
{
	Transform(glm::translate(model, translation));
}

void Entity::Rotate(const float angle, const glm::vec3& axis)
{
	Transform(glm::rotate(model, angle, axis));
}

void Entity::Scale(const glm::vec3& ratio)
{
	Transform(glm::scale(model, ratio));
}
