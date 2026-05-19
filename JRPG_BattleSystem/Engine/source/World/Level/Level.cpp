#include "World/Level/Level.h"
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

	scene.BeginPlay();
	sceneSubsystemCollection.BeginPlay();

	scene.SetupInputs(playerController);
}

void Level::FlushPendingAdds()
{
	scene.FlushPendingAdds();
	sceneSubsystemCollection.FlushPendingAdds();
}

void Level::UpdateTransform()
{
	scene.UpdateTransform();
}

void Level::UpdateInputs(InputManager* inputManager)
{
	playerController->UpdateInputs(inputManager);
}

void Level::Update(float deltaTime)
{
	scene.Update(deltaTime);
	sceneSubsystemCollection.Update(deltaTime);
}

void Level::FlushPendingDestroys()
{
	scene.FlushPendingDestroys();
	sceneSubsystemCollection.FlushPendingDestroys();
}

void Level::Unload()
{
	scene.Unload();
	sceneSubsystemCollection.Clear();

	delete playerController;
	playerController = nullptr;
}

void Level::BuildRenderQueue(RenderQueue& queue)
{
	scene.BuildRenderQueue(queue);
}