#include "UI/Widget.h"
#include "Scene/Scene.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

Widget::Widget()
{
	node.SetOwner(this);
}

void Widget::SetScene(Scene* newScene)
{ 
	if (scene)
	{
		scene->GetSceneGraph()->RemoveNode(&node);
	}
	scene = newScene;
	if (scene)
	{
		scene->GetSceneGraph()->AddNode(&node);
	}
}

Widget* Widget::GetParent()
{
	SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<Widget*>(parent->GetOwner());
	}
	return nullptr;
}

const Widget* Widget::GetParent() const
{
	const SceneNode* parent = node.GetParent();
	if (parent)
	{
		return dynamic_cast<const Widget*>(parent->GetOwner());
	}
	return nullptr;
}

void Widget::SetParent(Widget* element)
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

std::vector<Widget*> Widget::GetChildren()
{
	std::vector<SceneNode*> nodeChildren = node.GetChildren();
	std::vector<Widget*> children;

	for (SceneNode* child : nodeChildren)
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

void Widget::BeginDestroy()
{
	DetachFromHierarchy();
}

void Widget::MarkForDestruction()
{
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		if (scene)
		{
			scene->RegisterToDestroy(this);
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
	SceneNode* root = node.GetRoot();
	return root ? dynamic_cast<Widget*>(root->GetOwner()) : nullptr;
}

const Widget* Widget::GetRoot() const
{
	const SceneNode* root = node.GetRoot();
	return root ? dynamic_cast<const Widget*>(root->GetOwner()) : nullptr;
}