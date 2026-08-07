#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"
#include "World/Level/Scene/Actor.h"
#include "World/Level/Scene/Scene.h"
#include "Components/Camera/CameraComponent.h"

SpriteRendererComponent::SpriteRendererComponent(std::string textureName, std::string shaderName, glm::vec4 color)
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
	glm::vec2 mouseWorldPos = scene->GetActiveCamera()->ScreenToWorld(mousePos);

	glm::vec2 bounds = (size * GetWorldScale()) / 2.0f;
	glm::vec2 worldPos = GetWorldPosition();

	return mouseWorldPos.x >= worldPos.x - bounds.x &&
		mouseWorldPos.x <= worldPos.x + bounds.x &&
		mouseWorldPos.y >= worldPos.y - bounds.y &&
		mouseWorldPos.y <= worldPos.y + bounds.y;
}

void SpriteRendererComponent::AddToRenderQueue(RenderQueue& queue)
{
	if (isVisible)
	{
		queue.AddWorldItem(new RenderTextureItem(GetTransform().world, size, material), zOrder);
	}
}