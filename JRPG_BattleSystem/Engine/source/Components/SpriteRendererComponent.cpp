#include "Components/SpriteRendererComponent.h"
#include <glm/ext/matrix_transform.hpp>

SpriteRendererComponent::SpriteRendererComponent(std::string textureName, std::string shaderName, glm::vec3 color)
{
	sprite = new Sprite(textureName, shaderName, color);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	delete sprite;
	sprite = nullptr;
}
