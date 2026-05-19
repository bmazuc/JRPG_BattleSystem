#include "UI/Widget.h"
#include "World/Systems/UISystem.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

Widget::Widget()
{
	node.SetOwner(this);
}

void Widget::SetUISystem(UISystem* newUISystem)
{ 
	uiSystem = newUISystem;

	if (uiSystem)
	{
		if (!GetParent())
		{
			uiSystem->GetUIGraph()->AddNode(GetSceneNode());
		}
	}
}

Widget* Widget::GetParent()
{
	SpatialNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<Widget*>(parent->GetOwner());
	}
	return nullptr;
}

const Widget* Widget::GetParent() const
{
	const SpatialNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<const Widget*>(parent->GetOwner());
	}
	return nullptr;
}

void Widget::SetParent(Widget* element)
{
	if (!GetParent() && element)
	{
		uiSystem->GetUIGraph()->RemoveNode(GetSceneNode());
	}
	else if (GetParent() && !element)
	{
		uiSystem->GetUIGraph()->AddNode(GetSceneNode());
	}

	node.SetParent(element ? element->GetSceneNode() : nullptr);
}

std::vector<Widget*> Widget::GetChildren()
{
	std::vector<SpatialNode*> nodeChildren = node.GetChildren();
	std::vector<Widget*> children;

	for (SpatialNode* child : nodeChildren)
	{
		if (Widget* component = dynamic_cast<Widget*>(child->GetOwner()))
		{
			children.push_back(component);
		}
	}

	return children;
}

void Widget::UpdateTransform()
{
	node.UpdateTransform();
}

void Widget::DetachFromHierarchy()
{
	node.DetachFromHierarchy();
	uiSystem->GetUIGraph()->RemoveNode(&node);
}

void Widget::SetLocalPosition(glm::vec2 position)
{
	node.SetLocalPosition(position);
}

void Widget::SetLocalRotate(float rotate)
{
	node.SetLocalRotate(rotate);
}

void Widget::SetLocalScale(glm::vec2 scale)
{
	node.SetLocalScale(scale);
}

void Widget::SetWorldPosition(glm::vec2 position)
{
	node.SetWorldPosition(position);
}

void Widget::SetWorldRotate(float rotate)
{
	node.SetWorldRotate(rotate);
}

void Widget::SetWorldScale(glm::vec2 scale)
{
	node.SetWorldScale(scale);
}

void Widget::NativeBeginDestroy()
{
	DetachFromHierarchy();
	BeginDestroy();
}

void Widget::MarkForDestruction()
{
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		if (uiSystem)
		{
			uiSystem->RegisterToDestroy(this);
		}

		std::vector<Widget*> children = GetChildren();
		for (Widget* child : children)
		{
			child->MarkForDestruction();
		}
	}
}

Widget* Widget::GetRoot()
{
	SpatialNode* root = node.GetRoot();
	return root ? dynamic_cast<Widget*>(root->GetOwner()) : nullptr;
}

const Widget* Widget::GetRoot() const
{
	const SpatialNode* root = node.GetRoot();
	return root ? dynamic_cast<const Widget*>(root->GetOwner()) : nullptr;
}