#include "World/Level/Level.h"
#include "World/PlayerController.h"
#include "Core/Inputs/InputManager.h"


void Level::Load()
{
	playerController = new PlayerController();
	CreateLevel();
}

void Level::BeginPlay()
{
	scene.BeginPlay();
	sceneSubsystemCollection.BeginPlay();

	scene.SetPlayerController(playerController);
}

void Level::FlushPendingAdds()
{
	scene.FlushPendingAdds();
	sceneSubsystemCollection.FlushPendingAdds();
}

void Level::SyncSceneGraph()
{
	scene.SyncGraph();
}

void Level::UpdateSceneTransform()
{
	scene.UpdateTransform();
}

void Level::UpdateSceneEffectiveVisibity()
{
	scene.UpdateEffectiveVisibility();
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