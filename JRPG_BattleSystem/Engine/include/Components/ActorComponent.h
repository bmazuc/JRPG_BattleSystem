#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__

#include "Scene/Object.h"

class Actor;

/**
 *	Base class for components that define reusable behavior that can be added to different types of actors.
 */
class ActorComponent : public Object
{
public:
	/**
	 * Called once when the scene starts or component is created.
	 */
	virtual void BeginPlay() {}

	/**
	 * Called once per frame.
	 */
	virtual void Update(float deltaTime) {}

	/**
	 * Mark a component for destruction.
	 */
	void MarkForDestruction();

	Actor* GetOwner() { return owner; }
	const Actor* GetOwner() const { return owner; }
	void SetOwner(Actor* newOwner) { owner = newOwner; }

private:
	// Actor owning this component.
	Actor* owner = nullptr;
};

#endif // __COMPONENT_H_INCLUDED__
