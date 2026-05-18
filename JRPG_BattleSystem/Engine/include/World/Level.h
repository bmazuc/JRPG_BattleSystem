#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "World/Actor.h"
#include "UI/Widget.h"
#include "ObjectCollections/ActorCollection.h"
#include "ObjectCollections/LevelSubsystemCollection.h"
#include "SpatialGraph/SpatialGraph.h"
#include "World/SpawnInfos.h"
#include "UI/UserWidget.h"

class CameraComponent;
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

	CameraComponent* GetActiveCamera() { return activeCamera; }
	const CameraComponent* GetActiveCamera() const { return activeCamera; }
	
	/**
	 * Sets the camera used for rendering the world.
	 */
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }
	
	/**
	 * Returns actor internal raw container.
	 */
	std::vector<Actor*> GetActors() { return actorsCollection.GetCollection(); }
	const std::vector<Actor*> GetActors() const { return actorsCollection.GetCollection(); }

	/**
	 * Returns subsystems internal raw container.
	 */
	std::vector<LevelSubsystem*> GetSubsystems() { return sceneSubsystemCollection.GetCollection(); }
	const std::vector<LevelSubsystem*> GetSubsystems() const { return sceneSubsystemCollection.GetCollection(); }

	SpatialGraph* GetSceneGraph() { return &graph; }
	const SpatialGraph* GetSceneGraph() const { return &graph; }

	template<typename T, typename... Args>
	T* SpawnActor(std::string name, const ActorSpawnInfo& spawnInfo, Args&&... args);

	/**
	 * Retrieves first actor by name and type.
	 */
	template<typename T>
	T* GetActor(std::string name);

	template<typename T>
	const T* GetActor(std::string name) const;

	/**
	 * Retrieves first actor matching type.
	 */
	template<typename T>
	T* GetActor();

	template<typename T>
	const T* GetActor() const;

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

	/**
	 * Destruction requests
	 */

	void RegisterToDestroy(Actor* actor);

	glm::vec2 ScreenToWorld(glm::vec2 screenPos);

	void BuildRenderQueue(RenderQueue& queue)
	{
		graph.BuildRenderQueue(queue);
	}

	void SetWorld(World* newWorld) { world = newWorld; }

protected:
	World* world;

private:
	void InternalSpawnActor(Actor* actor, std::string name, const ActorSpawnInfo& spawnInfo);

	// Camera used for rendering calculations
	CameraComponent* activeCamera;

	PlayerController* playerController = nullptr;
	
	SpatialGraph graph;

	ActorCollection actorsCollection;
	LevelSubsystemCollection sceneSubsystemCollection;
};

#include "Level.inl"

#endif // __SCENE_H_INCLUDED__