#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

#include "Components/Component.h"
#include <glm/vec2.hpp>
#include <vector>
#include <string>
#include "Scene/ObjectCollections/ComponentCollection.h"

class Scene;
class PlayerController;

/**
 * Base class for all objects living in a scene.
 *
 * An Actor represents an entity that:
 * - has a transform hierarchy (via a root Component)
 * - can own multiple Components
 * - participates in scene lifecycle (BeginPlay / Update)
 * - can be attached to other actors (hierarchy)
 */
class Actor
{
public:
	Actor();
	virtual ~Actor();

	/**
	 * Called once when the scene starts or actor is spawned.
	 */
	virtual void BeginPlay() {}
	
	/**
	 * Called once per frame.
	 */
	virtual void Update(float deltaTime) {}

	/**
	 * Marks this actor for destruction.
	 * If destroyChildren is true, also destroys attached hierarchy.
	 */
	void Destroy(bool destroyChildren = false);

	/**
	 * Called during initialization to bind input logic.
	 */
	virtual void SetupInputs(PlayerController* playerController) {}

	/**
	 * Attaches this actor to another actor (hierarchy parenting).
	 */
	void AttachToActor(Actor* actor);

	/**
	 * Detaches this actor from its parent.
	 */
	void Detach();

	/**
	 * Updates transform hierarchy for this actor's root.
	 */
	void UpdateTransforms();
	void DetachFromHierarchy();
	
	/**
	 * Lifecycle hooks for components.
	 */

	void ComponentsBeginPlay();
	void UpdateComponents(float deltaTime);
	void ProcessComponentsAdd();
	void ProcessComponentsDestroy();

	/**
	 * Creates and attaches a component to this actor.
	 */
	template<typename T, typename... Args>
	T* SpawnComponent(std::string name, Component* parent, glm::vec2 localLocation, float localRotate, glm::vec2 localScale, Args&&... args)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
		T* component = new T(std::forward<Args>(args)...);
		InternalSpawnComponent(component, name, parent, localLocation, localRotate, localScale);
		return component;
	}

	/**
	 * Retrieves first compoent by name and type.
	 */
	template<typename T>
	T* GetComponent(std::string name)
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
		return componentsCollection.Get<T>(name);
	}

	template<typename T>
	const T* GetComponent(std::string name) const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
		return componentsCollection.Get<T>(name);
	}

	/**
	 * Retrieves first component matching type.
	 */
	template<typename T>
	T* GetComponent()
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
		return componentsCollection.Get<T>();
	}

	template<typename T>
	const T* GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must inherit Component");
		return componentsCollection.Get<T>();
	}
	
	/**
	 * Registers a component for destruction.
	 */
	void RegisterComponentsToDestroy(Component* component);

	Component* GetRoot() { return root; }
	const Component* GetRoot() const{ return root; }

	Actor* GetParent();
	const Actor* GetParent() const;

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }

	void SetScene(Scene* newScene);

	/*
	 *	Transform accessor
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
	// Optional identifier used for lookup.
	Scene* scene;

private:
	void InternalSpawnComponent(Component* component, std::string name, Component* parent, glm::vec2 localLocation, float localRotate, glm::vec2 localScale);

	Component* root;
	ComponentCollection componentsCollection;

	// Are actor mark for destruction ?
	bool isPendingDestroy = false;

	// Identifier used for lookup.
	std::string name = "";
};

#endif // __ACTOR_H_INCLUDED__