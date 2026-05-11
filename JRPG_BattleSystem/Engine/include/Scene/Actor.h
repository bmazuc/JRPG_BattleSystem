#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

#include "Components/Component.h"
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include "Scene/SceneObjectCollections/SceneObjectCollection.h"

class Scene;
class PlayerController;

/*
 *	Base class for anything that has a position, rotation, and scale in the game world
 */
class Actor
{
public:
	Actor();
	virtual ~Actor();

	/*
	 *	Behavior called after scene loading
	 */
	virtual void BeginPlay() {}
	/*
	 *	Behavior called each frame
	 */
	virtual void Update(float deltaTime) {}
	/*
	 *	Mark an actor for destroy
	 *	Future upgrade : Add a destroy with a timer
	 */ 
	void Destroy(bool destroyChildren = false);

	/*
	 *	Call after scene loading. Allow to link inputs and behaviour for this actor.
	 */
	virtual void SetupInputs(PlayerController* playerController) {}

	/*
	 *	Attach this actor root to another actor root.
	 *	@param actor the parent actor
	 */
	void AttachToActor(Actor* actor);
	/*
	 *	Detach this actor root from its parent.
	 */
	void Detach();

	/*
	 *	Update components transform.
	 */
	void UpdateTransforms();
	void DetachFromHierarchy();
	/*
	 *	Called each components init behavior. Called after scene loading.
	 */
	void ComponentsBeginPlay();
	/*
	 *	Called each components update behavior. Called each frame.
	 */
	void UpdateComponents(float deltaTime);
	/*
	 *	Destroy each components marked for destruction.
	 */
	void ProcessComponentsDestroy();

	/*
	 *	Create and add a component to this actor.
	 *	New component parent will be actor root.
	 */
	template<typename T, typename... Args>
	T* AddComponent(std::string name, Component* parent, glm::vec2 localLocation, float localRotate, glm::vec2 localScale, Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");

		T* component = new T(std::forward<Args>(args)...);
		
		InternalAddComponent(component, name, parent, localLocation, localRotate, localScale);

		return component;
	}

	/*
	 *	Get the first component of given name and type in this actor.
	 */
	template<typename T>
	T* GetComponent(std::string name)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
		return componentsCollection.Get<T>(name);
	}

	/*
	 *	Get the first component of given type in this actor.
	 */
	template<typename T>
	T* GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
		return componentsCollection.Get<T>();
	}
	
	/*
	 *	Call by component destroy. Register this component inside a list of components to destroy.
	 *	@param component the component to register
	 */
	void RegisterComponentsToDestroy(Component* component);

	Component* GetRoot() { return root; }
	const Component* GetRoot() const{ return root; }

	Actor* GetParent();
	const Actor* GetParent() const;

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }

	void SetScene(Scene* _scene);

	/*
	 *	Transform getter/setter
	 */

	glm::vec2 GetWorldPosition() const;
	float GetWorldRotate() const;
	glm::vec2 GetWorldScale() const;

	void SetWorldPosition(glm::vec2 position);
	void SetWorldRotate(float rotate);
	void SetWorldScale(glm::vec2 scale);

	glm::vec2 GetLocalPosition() const;
	float GetLocalRotate() const;
	glm::vec2 GetLocalScale() const;

	void SetLocalPosition(glm::vec2 position);
	void SetLocalRotate(float rotate);
	void SetLocalScale(glm::vec2 scale);

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

protected:
	// reference to the scene the actor lives in
	Scene* scene;

private:
	void InternalAddComponent(Component* component, std::string name, Component* parent, glm::vec2 localLocation, float localRotate, glm::vec2 localScale);

	Component* root;
	SceneObjectCollection<Component> componentsCollection;

	// Are actor mark for destruction ?
	bool isPendingDestroy = false;

	// Name associated to this actor. Useful to identify this actor.
	std::string name = "";
};

#endif // __ACTOR_H_INCLUDED__