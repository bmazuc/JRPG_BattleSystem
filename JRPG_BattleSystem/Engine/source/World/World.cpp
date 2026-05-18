#include "World/World.h"
#include "World/Systems/UISystem.h"

#include <SDL3/SDL.h>

LevelChangeRequest World::pendingLevelChangeRequest;

World::World()
{
	uiSystem = new UISystem();
}

void World::Init()
{
	LoadLevel(defaultLevel);
}

void World::Update(float deltaTime, InputManager* inputManager)
{
	if (activeLevel)
	{
		activeLevel->FlushPendingAdds();
		uiSystem->FlushPendingAdds();

		activeLevel->UpdateTransform();
		uiSystem->UpdateTransform();

		activeLevel->UpdateInputs(inputManager);
		uiSystem->UpdateInputs(inputManager);

		activeLevel->Update(deltaTime);
		uiSystem->Update(deltaTime);

		activeLevel->FlushPendingDestroys();
		uiSystem->FlushPendingDestroys();

		if (pendingLevelChangeRequest.type == LevelRequestType::ChangeLevel)
		{
			UnloadActiveLevel();
			LoadLevel(pendingLevelChangeRequest.nextLevelName);
			pendingLevelChangeRequest.type = LevelRequestType::None;
			pendingLevelChangeRequest.nextLevelName = "";
		}
	}
}

void World::LoadLevel(std::string name)
{
	auto it = levels.find(name);
	if (it != levels.end())
	{
		activeLevel = it->second;
		if (activeLevel)
		{
			activeLevel->Load();
			activeLevel->BeginPlay();
		}
		return;
	}

	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Level %s does not exist", name.c_str());
}

void World::UnloadActiveLevel()
{
	if (activeLevel)
	{
		uiSystem->OnLevelUnload();

		activeLevel->Unload();
		activeLevel = nullptr;
	}
}

World::~World()
{
	UnloadActiveLevel();

	delete uiSystem;
	uiSystem = nullptr;

	for (auto& it : levels)
	{
		delete it.second;
		it.second = nullptr;
	}

	levels.clear();
}

void World::BuildRenderQueue(RenderQueue& queue)
{
	if (activeLevel)
	{
		activeLevel->BuildRenderQueue(queue);
		uiSystem->BuildRenderQueue(queue);
	}
}

void World::RequestLevelChange(std::string sceneName)
{
	pendingLevelChangeRequest.type = LevelRequestType::ChangeLevel;
	pendingLevelChangeRequest.nextLevelName = sceneName;
}