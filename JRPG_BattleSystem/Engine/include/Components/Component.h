#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__

#include "Scene/SceneGraph/ISceneNodeOwner.h"
#include <string>

class Actor;

/*
 *	An element that can be attached to an Actor.
 */
class Component : public ISceneNodeOwner
{
public:
	Component();
	virtual ~Component() {};

	/*
	 *	Behavior called after scene loading
	 */
	virtual void BeginPlay() {}

	/*
	 *	Behavior called each frame
	 */
	virtual void Update(float deltaTime) {}

	/*
	 *	Mark a component for destroy
	 *	Future upgrade : Add a destroy with a timer
	 */
	void Destroy();

	bool HasParent() { return node.HasParent(); }
	void SetParent(Component* component);
	Component* GetParent();
	const Component* GetParent() const;
	std::vector<Component*> GetChildren();

	SceneNode* GetSceneNode() { return &node; }

	void UpdateTransform();
	void DetachFromHierarchy();

	/*
	 *	Transform getter/setter
	 */
	Transform2D& GetTransform() { return node.GetTransform(); }
	const Transform2D& GetTransform() const { return node.GetTransform(); }

	glm::vec2 GetWorldPosition() const { return node.GetWorldPosition(); }
	float GetWorldRotate() const { return node.GetWorldRotate(); }
	glm::vec2 GetWorldScale() const { return node.GetWorldScale(); }

	void SetWorldPosition(glm::vec2 position);
	void SetWorldRotate(float rotate);
	void SetWorldScale(glm::vec2 scale);

	glm::vec2 GetLocalPosition() const { return node.GetLocalPosition(); }
	float GetLocalRotate() const { return node.GetLocalRotate(); }
	glm::vec2 GetLocalScale() const { return node.GetLocalScale(); }

	void SetLocalPosition(glm::vec2 position);
	void SetLocalRotate(float rotate);
	void SetLocalScale(glm::vec2 scale);

	Actor* GetOwner() { return owner; }
	const Actor* GetOwner() const { return owner; }
	void SetOwner(Actor* _owner) { owner = _owner; }

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

private:
	// Name associated to this component. Useful to identify this component.
	std::string name = "";

	SceneNode node;

	// The actor owning this component.
	Actor* owner = nullptr;

	// Are component marked for destruction ?
	bool isPendingDestroy = false;
};

#endif // __COMPONENT_H_INCLUDED__
