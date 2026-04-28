#include "Scene/SceneManager.h"

#include <SDL3/SDL.h>

void SceneManager::Init()
{
	if (activeScene)
	{
		activeScene->CreateScene();
		activeScene->Init();
	}
}

void  SceneManager::SetActiveScene(std::string name)
{
	auto it = scenes.find(name);
	if (it != scenes.end())
	{
		activeScene = it->second;
		return;
	}

	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Scene %s does not exist", name.c_str());
}

void SceneManager::Update(float deltaTime)
{
	if (activeScene)
	{
		activeScene->UpdateTransforms();
		activeScene->Update(deltaTime);
		activeScene->ProcessDestroy();

		if (activeScene->HasRequest())
		{
			std::string newSceneName = activeScene->GetPendingRequest().newSceneName;
			activeScene->DestroyScene();
			SetActiveScene(newSceneName);
			activeScene->CreateScene();
			activeScene->Init();
		}
	}
}

SceneManager::~SceneManager()
{
	activeScene->DestroyScene();
	for (auto& it : scenes)
	{
		delete it.second;
		it.second = nullptr;
	}

	scenes.clear();
}