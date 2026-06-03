#include "Components/Camera/CameraComponent.h"
#include "World/Level/Scene/Actor.h"
#include "Core/Engine.h"
#include "Core/Window.h"

glm::vec2 CameraComponent::ScreenToWorld(glm::vec2 screenPos)
{
	const Engine* engine = Engine::Get();

	if (!engine)
	{ 
		return screenPos;
	}

	glm::vec2 worldPos = engine->GetWindow()->ScreenToViewport(screenPos);
	worldPos /= zoom;
	worldPos += GetWorldPosition();

	return worldPos;
}