#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include <string>
#include <vector>
#include <glm/vec2.hpp>

class CameraComponent;
class Actor;
class UIElement;
class Shader;
class Texture;
class PlayerController;
class InputManager;

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
	 *	Update the transforms of all UIElements and components.
	 */
	void UpdateTransforms();
	/*
	 *	Update all actors, UIElements, components.
	 */
	void Update(float deltaTime);
	/*
	*	Update player controller and UI inputs
	*/
	void UpdateInputs(InputManager* inputManager);
	/*
	 *	Process the destruction of actors, components and UI elements marked for destruction.
	 */
	void ProcessDestroy();

	CameraComponent* GetActiveCamera() { return activeCamera; }
	const CameraComponent* GetActiveCamera() const { return activeCamera; }
	// Set the camera used to compute the rendering view matrix
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }
	
	std::vector<Actor*> GetActors() { return actors; }
	const std::vector<Actor*> GetActors() const { return actors; }

	std::vector<UIElement*> GetUIElements() { return uiElements; }
	const std::vector<UIElement*> GetUIElements() const { return uiElements; }

	/*
	 *	Create and add an actor in the scene
	 */
	template<typename T, typename... Args>
	T* CreateActor(Args&&... args)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");

		T* actor = new T(std::forward<Args>(args)...);
		InternalAddActor(actor);
		return actor;
	}

	/*
	 *	Create and add an UI element in the scene
	 */
	template<typename T, typename... Args>
	T* CreateUIElement(Args&&... args)
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");

		T* element = new T(std::forward<Args>(args)...);
		InternalAddUIElement(element);
		return element;
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

	// Are the scene already loaded ?
	bool IsLoaded() const { return isLoaded; }

private:
	/*
	 *	Add the actor to the list of actors and call its begin play if scene is already loaded.
	 *	Also reduce the amount of code in .h
	 */
	void InternalAddActor(Actor* actor);
	/*
	 *	Add the UI element to the list of UI elements and call its begin play if scene is already loaded.
	 *	Also reduce the amount of code in .h
	 */
	void InternalAddUIElement(UIElement* element);

	// All actors living in the scene
	std::vector<Actor*> actors;
	// All actors marked for destruction
	std::vector<Actor*> actorsToDestroy;

	// Camera used to compute the rendering view matric
	CameraComponent* activeCamera;

	// The player controller associated to this scene
	PlayerController* playerController;
	// All UIElements living in the scene
	std::vector<UIElement*> uiElements;
	// All UIElements marked for destruction
	std::vector<UIElement*> uiElementsToDestroy;

	// Are the scene already loaded ?
	bool isLoaded = false;

	SceneRequest pendingRequest;
};

#endif // __SCENE_H_INCLUDED__