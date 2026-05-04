#include "Rendering/Material.h"
#include "Core/Resource/ResourceManager.h"

Material::Material()
	: color(glm::vec3(1,1,1))
{
	shader = &ResourceManager::GetShader("default");
	texture = &ResourceManager::GetTexture("default");
}

Material::Material(std::string textureName, std::string shaderName, glm::vec3 _color)
	: color(_color)
{
	shader = &ResourceManager::GetShader(shaderName);
	texture = &ResourceManager::GetTexture(textureName);
}

void Material::SetShader(std::string name)
{
	shader = &ResourceManager::GetShader(name);
}

void Material::SetTexture(std::string name)
{
	texture = &ResourceManager::GetTexture(name);
}