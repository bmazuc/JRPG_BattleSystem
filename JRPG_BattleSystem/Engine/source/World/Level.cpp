#include "World/Level.h"
#include "Components/ActorComponent.h"
#include "Components/Camera/CameraComponent.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"
#include "World/PlayerController.h"
#include "Core/Inputs/InputManager.h"
#include "UI/Button.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <UI/Image.h>

#include "Graphics/Texture.h"
#include "Rendering/Shader.h"

void Level::Load()
{
	CreateLevel();
}

void Level::BeginPlay()
{
	playerController = new PlayerController();

	graph.UpdateTransforms();

	actorsCollection.BeginPlay();
	sceneSubsystemCollection.BeginPlay();

	actorsCollection.SetupInputs(playerController);
}

void Level::FlushPendingAdds()
{
	actorsCollection.FlushPendingAdds();
	actorsCollection.ProcessComponentsAdd();
	sceneSubsystemCollection.FlushPendingAdds();
}

void Level::UpdateTransform()
{
	graph.UpdateTransforms();
}

void Level::UpdateInputs(InputManager* inputManager)
{
	playerController->UpdateInputs(inputManager);
}

void Level::Update(float deltaTime)
{
	actorsCollection.Update(deltaTime);
	sceneSubsystemCollection.Update(deltaTime);
}

void Level::FlushPendingDestroys()
{
	actorsCollection.FlushPendingDestroys();
	actorsCollection.ProcessComponentsDestroy();
	sceneSubsystemCollection.FlushPendingDestroys();
}

void Level::Unload()
{
	graph.Clear();

	actorsCollection.Clear();
	sceneSubsystemCollection.Clear();

	delete playerController;
	playerController = nullptr;
}

void Level::RegisterToDestroy(Actor* actor)
{
	actorsCollection.RegisterToDestroy(actor);
}

glm::vec2 Level::ScreenToWorld(glm::vec2 screenPos)
{
	glm::vec2 worldPos = screenPos;

	if (activeCamera)
	{
		worldPos -= activeCamera->GetWorldPosition();
		worldPos /= activeCamera->GetZoom();
	}

	return worldPos;
}

void Level::InternalSpawnActor(Actor* actor,std::string name, const ActorSpawnInfo& spawnInfo)
{
	actor->SetName(name);
	actor->SetLevel(this);
	actor->AttachToActor(spawnInfo.parent);

	if (spawnInfo.transformSpace == TransformSpace::World)
	{
		actor->SetWorldPosition(spawnInfo.location);
		actor->SetWorldRotate(spawnInfo.rotate);
		actor->SetWorldScale(spawnInfo.scale);
	}
	else
	{
		actor->SetLocalPosition(spawnInfo.location);
		actor->SetLocalRotate(spawnInfo.rotate);
		actor->SetLocalScale(spawnInfo.scale);
	}
	actorsCollection.RegisterToAdd(actor);
}