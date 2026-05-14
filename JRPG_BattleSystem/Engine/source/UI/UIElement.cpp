#include "UI/UIElement.h"
#include "Scene/Scene.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

UIElement::UIElement()
{
	node.SetOwner(this);
}

void UIElement::SetScene(Scene* newScene)
{ 
	scene = newScene;
	if (scene)
	{
		scene->GetSceneGraph()->AddNode(&node);
	}
}

UIElement* UIElement::GetParent()
{
	SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<UIElement*>(parent->GetOwner());
	}
	return nullptr;
}

const UIElement* UIElement::GetParent() const
{
	const SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<const UIElement*>(parent->GetOwner());
	}
	return nullptr;
}

void UIElement::SetParent(UIElement* element)
{
	if (element)
	{
		node.SetParent(element->GetSceneNode());
	}
	else
	{
		node.SetParent(nullptr);
	}
}

std::vector<UIElement*> UIElement::GetChildren()
{
	std::vector<SceneNode*> nodeChildren = node.GetChildren();
	std::vector<UIElement*> children;

	for (SceneNode* child : nodeChildren)
	{
		if (UIElement* component = dynamic_cast<UIElement*>(child->GetOwner()))
		{
			children.push_back(component);
		}
	}

	return children;
}

void UIElement::UpdateTransform()
{
	node.UpdateTransform();
}

void UIElement::DetachFromHierarchy()
{
	node.DetachFromHierarchy();
}

void UIElement::SetLocalPosition(glm::vec2 position)
{
	node.SetLocalPosition(position);
}

void UIElement::SetLocalRotate(float rotate)
{
	node.SetLocalRotate(rotate);
}

void UIElement::SetLocalScale(glm::vec2 scale)
{
	node.SetLocalScale(scale);
}

void UIElement::SetWorldPosition(glm::vec2 position)
{
	node.SetWorldPosition(position);
}

void UIElement::SetWorldRotate(float rotate)
{
	node.SetWorldRotate(rotate);
}

void UIElement::SetWorldScale(glm::vec2 scale)
{
	node.SetWorldScale(scale);
}

void UIElement::BeginDestroy()
{
	DetachFromHierarchy();
}

void UIElement::MarkForDestruction(bool markChildren)
{
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		if (scene)
		{
			scene->RegisterToDestroy(this);
		}

		if (markChildren)
		{
			std::vector<UIElement*> children = GetChildren();
			for (UIElement* child : children)
			{
				child->MarkForDestruction(true);
			}
		}
	}
}