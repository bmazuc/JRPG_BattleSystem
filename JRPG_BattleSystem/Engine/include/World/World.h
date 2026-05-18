#ifndef __SCENE_MANAGER_H_INCLUDED__
#define __SCENE_MANAGER_H_INCLUDED__

#include "World/Level.h"
#include "World/Systems/UISystem.h"
#include <string>
#include <SDL3/SDL.h>
#include <unordered_map>

class InputManager;

/**
 * Defines possible level transition requests.
 * Used by Level to communicate with World without direct coupling.
 */
enum class LevelRequestType
{
	None,		// No pending request
	ChangeLevel	// Request to switch to another level
};

/**
 * Represents a pending request made by a Level.
 * This is used to decouple Level logic from World execution.
 */
struct LevelChangeRequest
{
	// Type of request (none, change level, etc.)
	LevelRequestType type = LevelRequestType::None;

	// Target level name (used when type == ChangeLevel)
	std::string nextLevelName = "";
};

/**
 * World is responsible for:
 * - storing all available levels
 * - managing the active level
 * - handling level transitions (load / unload)
 */
class World
{
public:
	World();
	~World();

	/**
	 * Load the default level.
	 */
	void Init();

	/**
	 * Registers a new level type.
	 * The level is created immediately and its assets are loaded.
	 */
	template<typename T, typename... Args>
	void AddLevel(std::string name, Args&&... args)
	{
		static_assert(std::is_base_of<Level, T>::value, "T must inherit Level");

		auto it = levels.find(name);
		if (it != levels.end())
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Level %s already exist", name.c_str());
			return;
		}

		T* level = new T(std::forward<Args>(args)...);
		level->SetWorld(this);
		levels[name] = level;
		level->LoadAssets();
	}

	/**
	 * Defines which level should be loaded at engine startup.
	 */
	void SetDefaultLevel(std::string name) { defaultLevel = name; }
	
	/**
	 * Returns the currently active level.
	 */
	Level* GetActiveLevel() { return activeLevel; }
	const Level* GetActiveLevel() const { return activeLevel; }

	/**
	 * Updates the active level each frame.
	 *
	 * Handles:
	 * - update logic
	 * - input forwarding
	 * - level transition requests
	 */
	void Update(float deltaTime, InputManager* inputManager);

	UISystem* GetUISystem() { return uiSystem; }
	const UISystem* GetUISystem() const { return uiSystem; }

	void BuildRenderQueue(RenderQueue& queue);

	static void RequestLevelChange(std::string levelName);

private:
	/**
	 * Loads a level by name and makes it active.
	 */
	void LoadLevel(std::string name);

	/**
	 * Unloads the currently active level.
	 */
	void UnloadActiveLevel();

	// Level loaded at engine startup
	std::string defaultLevel;

	// Currently active level
	Level* activeLevel;

	// All registered level
	std::unordered_map<std::string, Level*> levels;

	UISystem* uiSystem;

	static LevelChangeRequest pendingLevelChangeRequest;
};


#endif // __SCENE_MANAGER_H_INCLUDED__