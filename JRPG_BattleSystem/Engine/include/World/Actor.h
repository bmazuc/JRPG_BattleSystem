#ifndef __ACTOR_H_INCLUDED__
#define __ACTOR_H_INCLUDED__

#include "Components/SceneComponent.h"
#include <glm/vec2.hpp>
#include <vector>
#include "World/ObjectCollections/ComponentCollection.h"
#include "World/SpawnInfos.h"

class Level;
class PlayerController;

/**
 * Base class for all objects living in a level.
 *
 * An Actor represents an entity that:
 * - has a transform hierarchy (via a root Component)
 * - can own multiple Components
 * - participates in level lifecycle (BeginPlay / Update)
 * - can be attached to other actors (hierarchy)
 */
class Actor : public Object
{
public:
	Actor();
	virtual ~Actor();

	/**
	 * Called once when the level starts or actor is spawned.
	 */
	virtual void BeginPlay() {}
	
	/**
	 * Called once per frame.
	 */
	virtual void Update(float deltaTime) {}

	/**
	 * Called before object destruction.
	 */
	void BeginDestroy() override;

	/**
	 * Marks this actor for destruction.
	 * If destroyChildren is true, also destroys attached hierarchy.
	 */
	void MarkForDestruction(bool markChildren = false);

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
	 * Creates and attaches an actor component to this actor.
	 */
	template<typename T, typename... Args>
	T* CreateComponent(std::string name, Args&&... args);

	/**
	 * Creates and attaches a level component to this actor.
	 */
	template<typename T, typename... Args>
	T* SpawnSceneComponent(std::string name, const SceneComponentSpawnInfo& spawnInfo, Args&&... args);

	/**
	 * Retrieves first compoent by name and type.
	 */
	template<typename T>
	T* GetComponent(std::string name);

	template<typename T>
	const T* GetComponent(std::string name) const;

	/**
	 * Retrieves first component matching type.
	 */
	template<typename T>
	T* GetComponent();

	template<typename T>
	const T* GetComponent() const;
	
	/**
	 * Registers a component for destruction.
	 */
	void RegisterComponentsToDestroy(ActorComponent* component);

	SceneComponent* GetRoot() { return root; }
	const SceneComponent* GetRoot() const{ return root; }

	Actor* GetParent();
	const Actor* GetParent() const;

	Level* GetLevel() { return level; }
	const Level* GetLevel() const { return level; }

	void SetLevel(Level* newLevel);

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

protected:
	// Level owning this actor.
	Level* level;

private:
	void InternalSpawnSceneComponent(SceneComponent* component, const SceneComponentSpawnInfo& spawnInfo);
	void RegisterComponent(ActorComponent* component, std::string name);

	SceneComponent* root;
	ComponentCollection componentsCollection;
};

#include "Actor.inl"

#endif // __ACTOR_H_INCLUDED__