#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "Scene/Actor.h"
#include "UI/Widget.h"
#include "ObjectCollections/ActorCollection.h"
#include "ObjectCollections/WidgetCollection.h"
#include "ObjectCollections/SceneSubsystemCollection.h"
#include "SceneGraph/SceneGraph.h"
#include "Scene/SpawnInfos.h"
#include "UI/UserWidget.h"

class CameraComponent;
class Shader;
class Texture;
class PlayerController;
class InputManager;
class UserWidget;

/**
 * Defines possible scene transition requests.
 * Used by Scene to communicate with SceneManager without direct coupling.
 */
enum class SceneRequestType
{
	None,		// No pending request
	ChangeScene	// Request to switch to another scene
};

/**
 * Represents a pending request made by a Scene.
 * This is used to decouple Scene logic from SceneManager execution.
 */
struct SceneRequest
{
	// Type of request (none, change scene, etc.)
	SceneRequestType type = SceneRequestType::None;

	// Target scene name (used when type == ChangeScene)
	std::string newSceneName = "";
};

/**
 * A Scene represents a complete game level or gameplay context.
 *
 * It owns and manages:
 * - Actors (game objects)
 * - widgets
 * - Scene graph (transform hierarchy)
 * - Active camera
 * - Input processing
 *
 * It also handles lifecycle:
 * Load → BeginPlay → Update → Unload
 */
class Scene
{
public:
	/**
	 * Override to load required assets (textures, shaders, etc.).
	 */
	virtual void LoadAssets() {}

	/**
	 * Override to create and initialize all actors/UI.
	 */
	virtual void CreateScene() {}

	/**
	 * Initializes the scene:
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
	 * Called once when the scene becomes active.
	 */
	void BeginPlay();

	/**
	 * Main update loop of the scene.
	 *
	 * Updates:
	 * - actors
	 * - components
	 * - UI
	 * - scene logic
	 */
	void Update(float deltaTime, InputManager* inputManager);

	/**
	 * Updates UI-specific input handling (hover, click, etc.).
	 */
	void UpdateUIInputs(InputManager* inputManager);

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
	 * Returns widget internal raw container.
	 */
	std::vector<Widget*> GetWidgets() { return widgetsCollection.GetCollection(); }
	const std::vector<Widget*> GetWidgets() const { return widgetsCollection.GetCollection(); }

	/**
	 * Returns subsystems internal raw container.
	 */
	std::vector<SceneSubsystem*> GetSubsystems() { return sceneSubsystemCollection.GetCollection(); }
	const std::vector<SceneSubsystem*> GetSubsystems() const { return sceneSubsystemCollection.GetCollection(); }

	SceneGraph* GetSceneGraph() { return &graph; }
	const SceneGraph* GetSceneGraph() const { return &graph; }

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
	T* CreateUserWidget(std::string name, const UISpawnInfo& spawnInfo, Args&&... args);

	/**
	* Retrieves first widget by name and type.
	*/
	template<typename T>
	T* GetUserWidget(std::string name);

	template<typename T>
	const T* GetUserWidget(std::string name) const;

	// Temp
	void AddWidget(Widget* widget) { widgetsCollection.Add(widget, isRuntime); }

	/**
	 * Retrieves first widget matching type.
	 */
	template<typename T>
	T* GetUserWidget();

	template<typename T>
	const T* GetUserWidget() const;

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
	void RegisterToDestroy(Widget* widget);

	/**
	 * Scene transitions
	 */

	void RequestSceneChange(std::string sceneName);
	SceneRequest GetPendingRequest() { return pendingRequest; }
	
	/**
	 * Return true if the scene request a scene change.
	 */
	bool HasRequest() const { return pendingRequest.type == SceneRequestType::ChangeScene; }

	glm::vec2 ScreenToWorld(glm::vec2 screenPos);

	void BuildRenderQueue(RenderQueue& queue)
	{
		graph.BuildRenderQueue(queue);
	}

	bool IsRuntime() { return isRuntime; }

private:
	void InternalSpawnActor(Actor* actor, std::string name, const ActorSpawnInfo& spawnInfo);
	void InternalSpawnUserWidget(UserWidget* userWidget, std::string name, const UISpawnInfo& spawnInfo);

	bool isRuntime = false;

	// Camera used for rendering calculations
	CameraComponent* activeCamera;

	PlayerController* playerController = nullptr;
	
	SceneGraph graph;

	ActorCollection actorsCollection;
	WidgetCollection widgetsCollection;
	SceneSubsystemCollection sceneSubsystemCollection;
	SceneRequest pendingRequest;
};

#include "Scene.inl"

#endif // __SCENE_H_INCLUDED__