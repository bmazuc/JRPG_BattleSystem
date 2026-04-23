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

	Transform GetTransform() { return transform; }

	glm::vec2 GetPosition() const { return transform.position; }
	float GetRotate() const { return transform.rotate; }
	glm::vec2 GetScale() const { return transform.scale; }

	void SetPosition(glm::vec2 position) { transform.position = position; }
	void SetRotate(float rotate) { transform.rotate = rotate; }
	void SetScale(glm::vec2 scale) { transform.scale = scale; }

	Actor* GetOwner() const { return owner; }
	void SetOwner(Actor* _owner) { owner = _owner; }

	void SetParent(Component* _parent);

private:
	void AddChild(Component* child);
	void RemoveChild(Component* child);

	Transform transform;

	Actor* owner;

	Component* parent;
	std::vector<Component*> children;
};

#endif // __COMPONENT_H_INCLUDED__
