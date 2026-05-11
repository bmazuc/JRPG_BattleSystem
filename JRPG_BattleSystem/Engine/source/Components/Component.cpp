#include "Components/Component.h"
#include "Scene/Actor.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

Component::Component()
{
	node.SetOwner(this);
}

Component* Component::GetParent()
{
	SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<Component*>(parent->GetOwner());
	}
	return nullptr;
}

const Component* Component::GetParent() const
{
	const SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<const Component*>(parent->GetOwner());
	}
	return nullptr;
}

void Component::SetParent(Component* component)
{
	if (component)
	{
		node.SetParent(component->GetSceneNode());
	}
	else
	{
		node.SetParent(nullptr);
	}
}

std::vector<Component*> Component::GetChildren()
{
	std::vector<SceneNode*> nodeChildren = node.GetChildren();
	std::vector<Component*> children;

	for (SceneNode* child : nodeChildren)
	{
		if (Component* component = dynamic_cast<Component*>(child->GetOwner()))
		{
			children.push_back(component);
		}
	}

	return children;
}

void Component::UpdateTransform()
{
	node.UpdateTransform();
}

void Component::DetachFromHierarchy()
{
	node.DetachFromHierarchy();
}

void Component::SetLocalPosition(glm::vec2 position)
{ 
	node.SetLocalPosition(position);
}

void Component::SetLocalRotate(float rotate)
{ 
	node.SetLocalRotate(rotate);
}

void Component::SetLocalScale(glm::vec2 scale)
{ 
	node.SetLocalScale(scale);
}

void Component::SetWorldPosition(glm::vec2 position)
{
	node.SetWorldPosition(position);
}

void Component::SetWorldRotate(float rotate)
{
	node.SetWorldRotate(rotate);
}

void Component::SetWorldScale(glm::vec2 scale)
{
	node.SetWorldScale(scale);
}

void Component::Destroy()
{ 
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		if (owner)
		{
			owner->RegisterComponentsToDestroy(this);
		}
	}
}

