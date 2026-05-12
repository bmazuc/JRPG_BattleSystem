#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "Scene/Actor.h"
#include "UI/UIElement.h"
#include "ObjectCollections/ActorCollection.h"
#include "ObjectCollections/UIElementCollection.h"
#include "SceneGraph/SceneGraph.h"
#include "Scene/SpawnInfos.h"

class CameraComponent;
class Shader;
class Texture;
class PlayerController;
class InputManager;

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
 * - UI elements
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
	 * Returns UI element internal raw container.
	 */
	std::vector<UIElement*> GetUIElements() { return uiElementsCollection.GetCollection(); }
	const std::vector<UIElement*> GetUIElements() const { return uiElementsCollection.GetCollection(); }

	SceneGraph* GetSceneGraph() { return &graph; }
	const SceneGraph* GetSceneGraph() const { return &graph; }

	template<typename T, typename... Args>
	T* SpawnActor(std::string name, const ActorSpawnInfo& spawnInfo, Args&&... args)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		T* actor = new T(std::forward<Args>(args)...);
		InternalSpawnActor(actor, name, spawnInfo);
		return actor;
	}

	/**
	 * Retrieves first actor by name and type.
	 */
	template<typename T>
	T* GetActor(std::string name)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		return actorsCollection.Get<T>(name);
	}

	template<typename T>
	const T* GetActor(std::string name) const
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		return actorsCollection.Get<T>(name);
	}

	/**
	 * Retrieves first actor matching type.
	 */
	template<typename T>
	T* GetActor()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		return actorsCollection.Get<T>();
	}

	template<typename T>
	const T* GetActor() const
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		return actorsCollection.Get<T>();
	}

	template<typename T, typename... Args>
	T* CreateUIElement(std::string name, const UISpawnInfo& spawnInfo, Args&&... args)
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		T* element = new T(std::forward<Args>(args)...);
		InternalSpawnUIElement(element, name, spawnInfo);
		return element;
	}

	/**
	* Retrieves first UI element by name and type.
	*/
	template<typename T>
	T* GetUIElement(std::string name)
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		return uiElementsCollection.Get<T>(name);
	}

	template<typename T>
	const T* GetUIElement(std::string name) const
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		return uiElementsCollection.Get<T>(name);
	}

	/**
	 * Retrieves first UI element matching type.
	 */
	template<typename T>
	T* GetUIElement()
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		return uiElementsCollection.Get<T>();
	}

	template<typename T>
	const T* GetUIElement() const
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		return uiElementsCollection.Get<T>();
	}

	/**
	 * Destruction requests
	 */

	void RegisterToDestroy(Actor* actor);
	void RegisterToDestroy(UIElement* uiElement);

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

private:
	void InternalSpawnActor(Actor* actor, std::string name, const ActorSpawnInfo& spawnInfo);
	void InternalSpawnUIElement(UIElement* element, std::string name, const UISpawnInfo& spawnInfo);

	// Camera used for rendering calculations
	CameraComponent* activeCamera;

	PlayerController* playerController = nullptr;
	
	SceneGraph graph;

	ActorCollection actorsCollection;
	UIElementCollection uiElementsCollection;

	SceneRequest pendingRequest;
};

#endif // __SCENE_H_INCLUDED__