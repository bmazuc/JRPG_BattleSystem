#include "Components/SceneComponent.h"

SceneComponent::SceneComponent()
{
	node.SetOwner(this);
}

void SceneComponent::BeginDestroy()
{
	DetachFromHierarchy();
}

SceneComponent* SceneComponent::GetParent()
{
	SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<SceneComponent*>(parent->GetOwner());
	}
	return nullptr;
}

const SceneComponent* SceneComponent::GetParent() const
{
	const SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<const SceneComponent*>(parent->GetOwner());
	}
	return nullptr;
}

void SceneComponent::SetParent(SceneComponent* component)
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

std::vector<SceneComponent*> SceneComponent::GetChildren()
{
	std::vector<SceneNode*> nodeChildren = node.GetChildren();
	std::vector<SceneComponent*> children;

	for (SceneNode* child : nodeChildren)
	{
		if (SceneComponent* component = dynamic_cast<SceneComponent*>(child->GetOwner()))
		{
			children.push_back(component);
		}
	}

	return children;
}

void SceneComponent::UpdateTransform()
{
	node.UpdateTransform();
}

void SceneComponent::DetachFromHierarchy()
{
	node.DetachFromHierarchy();
}

void SceneComponent::SetLocalPosition(glm::vec2 position)
{
	node.SetLocalPosition(position);
}

void SceneComponent::SetLocalRotate(float rotate)
{
	node.SetLocalRotate(rotate);
}

void SceneComponent::SetLocalScale(glm::vec2 scale)
{
	node.SetLocalScale(scale);
}

void SceneComponent::SetWorldPosition(glm::vec2 position)
{
	node.SetWorldPosition(position);
}

void SceneComponent::SetWorldRotate(float rotate)
{
	node.SetWorldRotate(rotate);
}

void SceneComponent::SetWorldScale(glm::vec2 scale)
{
	node.SetWorldScale(scale);
}