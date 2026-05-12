#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__

#include "Scene/SceneGraph/ISceneNodeOwner.h"
#include <string>

class Actor;

/**
 *	Base class for components that define reusable behavior that can be added to different types of actors.
 */
class Component : public ISceneNodeOwner
{
public:
	Component();
	virtual ~Component() {};

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
	void Destroy();

	bool HasParent() { return node.HasParent(); }
	void SetParent(Component* component);
	Component* GetParent();
	const Component* GetParent() const;
	std::vector<Component*> GetChildren();

	SceneNode* GetSceneNode() { return &node; }

	void UpdateTransform();
	void DetachFromHierarchy();

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
	void SetOwner(Actor* newOwner) { owner = newOwner; }

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

private:
	// Identifier used for lookup.
	std::string name = "";

	SceneNode node;

	// Actor owning this component.
	Actor* owner = nullptr;

	// Are this component marked for destruction ?
	bool isPendingDestroy = false;
};

#endif // __COMPONENT_H_INCLUDED__
