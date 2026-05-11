#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include "Scene/Actor.h"
#include "UI/UIElement.h"
#include "SceneObjectCollections/ActorCollection.h"
#include "SceneObjectCollections/UIElementCollection.h"
#include "SceneGraph/SceneGraph.h"

class CameraComponent;
class Shader;
class Texture;
class PlayerController;
class InputManager;

struct SpawnInfo
{
public:
	SpawnInfo(TransformSpace _transformSpace, glm::vec2 _location, float _rotate, glm::vec2 _scale)
		: transformSpace(_transformSpace), location(_location), rotate(_rotate), scale(_scale) { }

	virtual ~SpawnInfo() = 0;
	glm::vec2 location = glm::vec2(0.0f, 0.0f);
	float rotate = 0.0f;
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
	TransformSpace transformSpace = TransformSpace::World;
};

struct ActorSpawnInfo : SpawnInfo
{
public:
	ActorSpawnInfo(Actor* _parent = nullptr, TransformSpace _transformSpace = TransformSpace::World, glm::vec2 _location = glm::vec2(0.0f, 0.0f), float _rotate = 0.0f, glm::vec2 _scale = glm::vec2(1.0f, 1.0f))
		: parent(_parent), SpawnInfo(_transformSpace, _location, _rotate, _scale) {}
	~ActorSpawnInfo() = default;

	Actor* parent = nullptr;
};

struct UISpawnInfo : SpawnInfo
{
public:
	UISpawnInfo(UIElement* _parent = nullptr, TransformSpace _transformSpace = TransformSpace::World, glm::vec2 _location = glm::vec2(0.0f, 0.0f), float _rotate = 0.0f, glm::vec2 _scale = glm::vec2(1.0f, 1.0f))
		: parent(_parent), SpawnInfo(_transformSpace, _location, _rotate, _scale) {}
	~UISpawnInfo() = default;

	UIElement* parent = nullptr;
};

/*
 *	Request type that a scene can send.
 */
enum class SceneRequestType
{
	None,
	ChangeScene
};

/*
 *	Represents a change scene request
 */
struct SceneRequest
{
	SceneRequestType type = SceneRequestType::None;
	std::string newSceneName = "";
};

/*
 *	Represent a game level.
 */
class Scene
{
public:
	/*
	 *	Should be override and fill with all calls to ResourceManager to load needed assets
	 */
	virtual void LoadAssets() {}
	/*
	 *	Should be override and fill with all actors, components and UI elements creation and setup.
	 */
	virtual void CreateScene() {}

	/*
	 *	Call CreateScene then set isLoaded to true.
	 */
	void Load();

	/*
	 *	Destroy all actors and UIElements living in the scene.
	 */
	void Unload();
	
	/*
	 *	Initialize all actors, UIElements, components.
	 */
	void BeginPlay();

	/*
	 *	Update all actors, UIElements, components.
	 */
	void Update(float deltaTime, InputManager* inputManager);

	void UpdateUIInputs(InputManager* inputManager);

	CameraComponent* GetActiveCamera() { return activeCamera; }
	const CameraComponent* GetActiveCamera() const { return activeCamera; }
	// Set the camera used to compute the rendering view matrix
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }
	
	std::vector<Actor*> GetActors() { return actorsCollection.GetCollection(); }
	const std::vector<Actor*> GetActors() const { return actorsCollection.GetCollection(); }

	std::vector<UIElement*> GetUIElements() { return uiElementsCollection.GetCollection(); }
	const std::vector<UIElement*> GetUIElements() const { return uiElementsCollection.GetCollection(); }

	SceneGraph* GetSceneGraph() { return &graph; }
	const SceneGraph* GetSceneGraph() const { return &graph; }

	/*
	 *	Create and spawn an actor in the scene
	 */
	template<typename T, typename... Args>
	T* SpawnActor(std::string name, const ActorSpawnInfo& spawnInfo, Args&&... args)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		T* actor = new T(std::forward<Args>(args)...);
		InternalSpawnActor(actor, name, spawnInfo);
		return actor;
	}

	/*
	 *	Get the first actor of given name and type from the scene
	 */
	template<typename T>
	T* GetActor(std::string name)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		return actorsCollection.Get<T>(name);
	}

	/*
	 *	Get the first actor of given type from the scene
	 */
	template<typename T>
	T* GetActor()
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");
		return actorsCollection.Get<T>();
	}

	/*
	 *	Create and add an UI element in the scene.
	 */
	template<typename T, typename... Args>
	T* CreateUIElement(std::string name, const UISpawnInfo& spawnInfo, Args&&... args)
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		T* element = new T(std::forward<Args>(args)...);
		InternalSpawnUIElement(element, name, spawnInfo);
		return element;
	}

	/*
	 *	Get the first UI element of given name and type from the scene
	 */
	template<typename T>
	T* GetUIElement(std::string name)
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		return uiElementsCollection.Get<T>(name);
	}

	/*
	 *	Get the first UI element of given type from the scene
	 */
	template<typename T>
	T* GetUIElement()
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");
		return uiElementsCollection.Get<T>();
	}

	/*
	 *	Call by actor destroy. Register this actor inside a list of actors to destroy.
	 *	@param actor the actor to register
	 */
	void RegisterToDestroy(Actor* actor);
	/*
	 *	Call by ui element destroy. Register this ui element inside a list of ui elements to destroy.
	 *	@param uiElement the ui element to register
	 */
	void RegisterToDestroy(UIElement* uiElement);

	/*
	 *	Request a scene change.
	 *	@param sceneName the next scene name
	 */
	void RequestSceneChange(std::string sceneName);
	SceneRequest GetPendingRequest() { return pendingRequest; }
	// Does the scene request a scene change ?
	bool HasRequest() const { return pendingRequest.type == SceneRequestType::ChangeScene; }

	/* 
	 *	Convert a screen position to a world position
	 *	@param screenPos screen position to convert
	 *	@return converted screen position in world position
	 */ 
	glm::vec2 ScreenToWorld(glm::vec2 screenPos);

private:
	void InternalSpawnActor(Actor* actor, std::string name, const ActorSpawnInfo& spawnInfo);
	void InternalSpawnUIElement(UIElement* element, std::string name, const UISpawnInfo& spawnInfo);

	// Camera used to compute the rendering view matric
	CameraComponent* activeCamera;

	// The player controller associated to this scene
	PlayerController* playerController;
	
	SceneGraph graph;

	ActorCollection actorsCollection;
	UIElementCollection uiElementsCollection;

	SceneRequest pendingRequest;
};

#endif // __SCENE_H_INCLUDED__