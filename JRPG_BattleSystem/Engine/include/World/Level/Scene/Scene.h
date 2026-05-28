#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "World/ObjectCollections/ActorCollection.h"
#include "World/SpatialGraph/SpatialGraph.h"

class CameraComponent;
class PlayerController;

/**
 * Runtime container for gameplay actors and world hierarchy.
 * A Scene manages:
 * - actor lifetime
 * - transform hierarchy updates
 * - render queue generation
 * - active camera selection
 *
 * Scenes are owned by Levels.
 */
class Scene
{
public:
	/**
	 * Cleans all runtime objects from memory.
	 */
	void Unload();

	/**
	 * Called once when the level becomes active.
	 */
	void BeginPlay();
	void SetPlayerController(PlayerController* playerController);

	void FlushPendingAdds();
	void SyncGraph();
	void UpdateTransform();
	void Update(float deltaTime);
	void FlushPendingDestroys();

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

	/**
	 * Returns actor internal raw container.
	 */
	std::vector<Actor*> GetActors() { return actorsCollection.GetCollection(); }
	const std::vector<Actor*> GetActors() const { return actorsCollection.GetCollection(); }

	void RegisterToDestroy(Actor* actor);

	SpatialGraph* GetSceneGraph() { return &graph; }
	const SpatialGraph* GetSceneGraph() const { return &graph; }
	
	/**
	 * Builds the frame render queue from all renderable runtime objects.
	 */
	void BuildRenderQueue(RenderQueue& queue)
	{
		graph.BuildRenderQueue(queue, nullptr);
	}

	CameraComponent* GetActiveCamera() { return activeCamera; }
	const CameraComponent* GetActiveCamera() const { return activeCamera; }

	/**
	 * Sets the camera used for rendering the world.
	 */
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }

	glm::vec2 ScreenToWorld(glm::vec2 screenPos);

	void RegisterDirtyActor(Actor* actor)
	{
		dirtyActors.push_back(actor);
	}

private:
	void InternalSpawnActor(Actor* actor, std::string name, const ActorSpawnInfo& spawnInfo);

	// Camera used for rendering calculations
	CameraComponent* activeCamera;

	SpatialGraph graph;

	ActorCollection actorsCollection;
	std::vector<Actor*> dirtyActors;
};

#include "Scene.inl"

#endif // __SCENE_H_INCLUDED__