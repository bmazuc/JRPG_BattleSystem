#ifndef __SCENE_MANAGER_H_INCLUDED__
#define __SCENE_MANAGER_H_INCLUDED__

#include "Scene/Scene.h"

#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>

class InputManager;

/**
 * SceneManager is responsible for:
 * - storing all available scenes
 * - managing the active scene
 * - handling scene transitions (load / unload)
 */
class SceneManager
{
public:
	~SceneManager();

	/**
	 * Load the default scene.
	 */
	void Init();

	/**
	 * Registers a new scene type.
	 * The scene is created immediately and its assets are loaded.
	 */
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

	/**
	 * Defines which scene should be loaded at engine startup.
	 */
	void SetDefaultScene(std::string name) { defaultScene = name; }
	
	/**
	 * Returns the currently active scene.
	 */
	Scene* GetActiveScene() { return activeScene; }
	const Scene* GetActiveScene() const { return activeScene; }

	/**
	 * Updates the active scene each frame.
	 *
	 * Handles:
	 * - update logic
	 * - input forwarding
	 * - scene transition requests
	 */
	void Update(float deltaTime, InputManager* inputManager);

private:
	/**
	 * Loads a scene by name and makes it active.
	 */
	void LoadScene(std::string name);

	/**
	 * Unloads the currently active scene.
	 */
	void UnloadActiveScene();

	// Scene loaded at engine startup
	std::string defaultScene;

	// Currently active scene
	Scene* activeScene;

	// All registered scene
	std::unordered_map<std::string, Scene*> scenes;
};


#endif // __SCENE_MANAGER_H_INCLUDED__