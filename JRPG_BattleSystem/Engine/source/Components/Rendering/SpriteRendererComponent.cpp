#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"

SpriteRendererComponent::SpriteRendererComponent(std::string textureName, std::string shaderName, glm::vec3 color)
{
	material = new Material(textureName, shaderName, color);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	delete material;
	material = nullptr;
}
