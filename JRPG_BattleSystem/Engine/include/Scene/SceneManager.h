#pragma once

#include "Scene/Scene.h"

#include <string>
#include <SDL3/SDL.h>

class SceneManager
{
public:
	~SceneManager();
	void Init();

	template<typename T, typename... Args>
	void AddScene(std::string name, Args&&... args)
	{
		static_assert(std::is_base_of<Scene, T>::value, "T must inherit Scene");

		auto it = scenes.find(name);
		if (it != scenes.end())
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Scene %s already exist", name.c_str());
			return;
		}

		T* scene = new T(std::forward<Args>(args)...);
		scenes[name] = scene;
		scene->LoadAssets();
	}

	void SetDefaultScene(std::string name) { defaultScene = name; }
	Scene* GetActiveScene() const { return activeScene; }
	void Update(float deltaTime);

private:
	void LoadScene(std::string name);
	void UnloadActiveScene();

	std::string defaultScene;

	Scene* activeScene;
	std::unordered_map<std::string, Scene*> scenes;
};

