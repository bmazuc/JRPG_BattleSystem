#include "Rendering/Material.h"
#include "Core/Resource/ResourceManager.h"

Material::Material(std::string textureName, std::string shaderName, glm::vec3 _color)
	: color(_color)
{
	shader = &ResourceManager::GetShader(shaderName);
	texture = &ResourceManager::GetTexture(textureName);
}