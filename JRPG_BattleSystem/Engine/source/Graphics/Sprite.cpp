#include "Graphics/Sprite.h"
#include "Core/Resource/ResourceManager.h"
#include "Rendering/Material.h"

Sprite::Sprite(std::string textureName, std::string shaderName, glm::vec3 color)
{
	material = new Material(textureName, shaderName, color);
}

Sprite::~Sprite()
{
	delete material;
	material = nullptr;
}