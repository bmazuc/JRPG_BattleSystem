#ifndef __SCENE_MANAGER_H_INCLUDED__
#define __SCENE_MANAGER_H_INCLUDED__

#include "Scene/Scene.h"

#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>

class InputManager;

/*
 *	Manage the differents scenes (levels) of the game.
 *	Store the scenes, load and unload them, handle the scene
 *	transitions, handle active scene
 */
class SceneManager
{
public:
	~SceneManager();
	/*
	 *	Load the default scene.
	 */
	void Init();

	/*
	 *  Create and register a scene.
	 *  @param name the key used to register the shader
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

	/*
	 *	Set the scene load at engine start.
	 *	@param name the key used to register the scene
	 */
	void SetDefaultScene(std::string name) { defaultScene = name; }
	/*
	 *	Get the scene currently loaded.
	 */
	Scene* GetActiveScene() { return activeScene; }
	/*
	 *	Get the scene currently loaded.
	 */
	const Scene* GetActiveScene() const { return activeScene; }

	/*
	 *	Update the active scene. Called each frame.
	 */
	void UpdateInputs(float deltaTime, InputManager* inputManager);

private:
	/*
	 *	Create the scene associated to the key.
	 *	@param name the key used to register the scene
	 */
	void LoadScene(std::string name);
	/*
	 *	Destroy the current scene.
	 */
	void UnloadActiveScene();

	// The scene load at engine start.
	std::string defaultScene;

	// The scene currently loaded
	Scene* activeScene;
	std::unordered_map<std::string, Scene*> scenes;
};


#endif // __SCENE_MANAGER_H_INCLUDED__