#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"
#include "Scene/Actor.h"
#include "Scene/Scene.h"

SpriteRendererComponent::SpriteRendererComponent(std::string textureName, std::string shaderName, glm::vec3 color)
{
	material = new Material(textureName, shaderName, color);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
	delete material;
	material = nullptr;
}

bool SpriteRendererComponent::IsHovered(glm::vec2 mousePos)
{
	if (!IsVisible())
	{
		return false;
	}

	Scene* scene = GetOwner()->GetScene();
	glm::vec2 mouseWorldPos = scene->ScreenToWorld(mousePos);

	glm::vec2 bounds = (size * GetWorldScale()) / 2.0f;
	glm::vec2 worldPos = GetWorldPosition();

	return mouseWorldPos.x >= worldPos.x - bounds.x &&
		mouseWorldPos.x <= worldPos.x + bounds.x &&
		mouseWorldPos.y >= worldPos.y - bounds.y &&
		mouseWorldPos.y <= worldPos.y + bounds.y;
}

void SpriteRendererComponent::AddToRenderQueue(RenderQueue& queue)
{
	queue.AddItem(new RenderTextureItem(GetTransform().world, size, material), zOrder);
}