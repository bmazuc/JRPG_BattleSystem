#include "Scene/SceneManager.h"

#include <SDL3/SDL.h>

void SceneManager::Init()
{
	LoadScene(defaultScene);
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
			UnloadActiveScene();
			LoadScene(newSceneName);
		}
	}
}

void SceneManager::LoadScene(std::string name)
{
	auto it = scenes.find(name);
	if (it != scenes.end())
	{
		activeScene = it->second;
		if (activeScene)
		{
			activeScene->CreateScene();
			activeScene->Init();
		}
		return;
	}

	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Scene %s does not exist", name.c_str());
}

void SceneManager::UnloadActiveScene()
{
	if (activeScene)
	{
		activeScene->DestroyScene();
		activeScene = nullptr;
	}
}

SceneManager::~SceneManager()
{
	UnloadActiveScene();
	for (auto& it : scenes)
	{
		delete it.second;
		it.second = nullptr;
	}

	scenes.clear();
}