#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__

#include "Core/Math/Transform2D.h"
#include <vector>

class Actor;

/*
 *	An element that can be attached to an Actor.
 */
class Component
{
public:
	virtual ~Component();

	/*
	 *	Behavior called after scene loading
	 */
	virtual void Init() {}

	/*
	 *	Behavior called each frame
	 */
	virtual void Update(float deltaTime) {}
	/*
	 *	If marked dirty, update this component transform.
	 *	Called UpdateTransform() on children.
	 */
	void UpdateTransform();

	/*
	 *	Mark a component for destroy
	 *	Future upgrade : Add a destroy with a timer
	 */
	void Destroy();

	/*
	 *	Transform getter/setter
	 */

	Transform2D GetTransform() const { return transform; }

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

	Actor* GetOwner() { return owner; }
	const Actor* GetOwner() const { return owner; }
	void SetOwner(Actor* _owner) { owner = _owner; }

	Component* GetParent() { return parent; }
	const Component* GetParent() const { return parent; }
	void SetParent(Component* _parent);
	// Does this component have a parent ?
	bool HasParent() const { return parent; }

private:
	void AddChild(Component* child);
	void RemoveChild(Component* child);
	// Is this component an ancestor of the specified component ?
	bool IsAncestorOf(Component* component);
	Component* GetRoot();

	// Mark this component as dirty
	void SetDirty();

	Transform2D transform;

	// The actor owning this component.
	Actor* owner;

	Component* parent;
	std::vector<Component*> children;
	// Should this component update its transform ?
	bool isDirty = true;
	// Are component marked for destruction ?
	bool isPendingDestroy = false;
};

#endif // __COMPONENT_H_INCLUDED__
