#ifndef __LEVEL_H_INCLUDED__
#define __LEVEL_H_INCLUDED__

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "World/Level/Scene/Actor.h"
#include "UI/Widget.h"
#include "World/ObjectCollections/LevelSubsystemCollection.h"
#include "World/SpawnInfos.h"
#include "World/Level/Scene/Scene.h"

class Shader;
class Texture;
class PlayerController;
class InputManager;
class World;

/**
 * A Level represents a complete game level or gameplay context.
 *
 * It owns and manages:
 * - Actors (game objects)
 * - Level graph (transform hierarchy)
 * - Active camera
 * - Input processing
 *
 * It also handles lifecycle:
 * Load → BeginPlay → Update → Unload
 */
class Level
{
public:
	/**
	 * Override to load required assets (textures, shaders, etc.).
	 */
	virtual void LoadAssets() {}

	/**
	 * Override to create and initialize all actors/UI.
	 */
	virtual void CreateLevel() {}

	/**
	 * Initializes the level:
	 * - loads content
	 * - builds objects
	 * - prepares runtime state
	 */
	void Load();

	/**
	 * Cleans all runtime objects from memory.
	 */
	void Unload();
	
	/**
	 * Called once when the level becomes active.
	 */
	void BeginPlay();

	void FlushPendingAdds();
	void UpdateTransform();
	void UpdateInputs(InputManager* inputManager);
	void Update(float deltaTime);
	void FlushPendingDestroys();

	Scene* GetScene() { return &scene; }
	const Scene* GetScene() const { return &scene; }

	/**
	 * Returns subsystems internal raw container.
	 */
	std::vector<LevelSubsystem*> GetSubsystems() { return sceneSubsystemCollection.GetCollection(); }
	const std::vector<LevelSubsystem*> GetSubsystems() const { return sceneSubsystemCollection.GetCollection(); }

	template<typename T, typename... Args>
	T* AddSubsystem(std::string name, Args&&... args);

	/**
	 * Retrieves first subsystem by name and type.
	 */
	template<typename T>
	T* GetSubsystem(std::string name);

	template<typename T>
	const T* GetSubsystem(std::string name) const;

	/**
	 * Retrieves first subsystem matching type.
	 */
	template<typename T>
	T* GetSubsystem();

	template<typename T>
	const T* GetSubsystem() const;

	void BuildRenderQueue(RenderQueue& queue);

	void SetWorld(World* newWorld) { world = newWorld; }

protected:
	World* world;

private:
	Scene scene;

	PlayerController* playerController = nullptr;

	LevelSubsystemCollection sceneSubsystemCollection;
};

#include "Level.inl"

#endif // __LEVEL_H_INCLUDED__