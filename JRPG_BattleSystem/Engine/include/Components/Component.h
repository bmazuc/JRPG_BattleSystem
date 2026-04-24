#ifndef __COMPONENT_H_INCLUDED__
#define __COMPONENT_H_INCLUDED__

#include "Transform.h"
#include <vector>

class Actor;

class Component
{
public:
	virtual ~Component() = default;

	virtual void Update(float deltaTime) {}
	void UpdateTransform();

	Transform GetTransform() const { return transform; }

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

	Actor* GetOwner() const { return owner; }
	void SetOwner(Actor* _owner) { owner = _owner; }

	void SetParent(Component* _parent);
	bool HasParent() const { return parent; }

private:
	void AddChild(Component* child);
	void RemoveChild(Component* child);
	bool IsAncestorOf(Component* component);
	Component* GetRoot();

	void SetDirty();

	Transform transform;

	Actor* owner;

	Component* parent;
	std::vector<Component*> children;
	bool isDirty = true;
};

#endif // __COMPONENT_H_INCLUDED__
