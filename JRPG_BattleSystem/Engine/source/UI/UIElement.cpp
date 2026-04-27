#include "UI/UIElement.h"
#include "Scene/Scene.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

void UIElement::AddChild(UIElement* child)
{
	children.push_back(child);
}

void UIElement::RemoveChild(UIElement* child)
{
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

bool UIElement::IsAncestorOf(UIElement* element)
{
	if (this == element)
	{
		return true;
	}

	for (UIElement* child : children)
	{
		if (child->IsAncestorOf(element))
		{
			return true;
		}
	}

	return false;
}

void UIElement::UpdateTransform()
{
	if (isDirty)
	{
		glm::mat4 m(1.0f);

		m = glm::translate(m, glm::vec3(transform.position, 0.0f));
		m = glm::rotate(m, glm::radians(transform.rotate), glm::vec3(0.0f, 0.0f, 1.0f));
		m = glm::scale(m, glm::vec3(transform.scale, 1.0f));

		if (parent)
		{
			transform.world = parent->transform.world * m;
		}
		else
		{
			transform.world = m;
		}

		isDirty = false;
	}

	for (UIElement* child : children)
	{
		child->UpdateTransform();
	}
}

void UIElement::SetParent(UIElement* _parent)
{
	if (parent != _parent)
	{
		if (_parent && _parent->IsAncestorOf(this))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot attach parent to one of its children.");
			return;
		}

		GetRoot()->UpdateTransform();

		// Save current world
		glm::vec2 worldPos = GetWorldPosition();
		float worldRot = GetWorldRotate();
		glm::vec2 worldScale = GetWorldScale();

		if (parent)
		{
			parent->RemoveChild(this);
		}

		parent = _parent;

		if (parent)
		{
			parent->AddChild(this);
		}

		// Restore local
		SetWorldPosition(worldPos);
		SetWorldRotate(worldRot);
		SetWorldScale(worldScale);
	}
}

glm::vec2 UIElement::GetLocalPosition() const
{ 
	return transform.position;
}

float UIElement::GetLocalRotate() const
{
	return transform.rotate;
}

glm::vec2 UIElement::GetLocalScale() const
{
	return transform.scale;
}

void UIElement::SetLocalPosition(glm::vec2 position)
{
	transform.position = position;
	SetDirty();
}

void UIElement::SetLocalRotate(float rotate)
{
	transform.rotate = rotate;
	SetDirty();
}

void UIElement::SetLocalScale(glm::vec2 scale)
{
	transform.scale = scale;
	SetDirty();
}

glm::vec2 UIElement::GetWorldPosition() const
{
	return glm::vec2(transform.world[3]);
}

float UIElement::GetWorldRotate() const
{
	return glm::degrees(atan2(transform.world[1][0], transform.world[0][0]));
}

glm::vec2 UIElement::GetWorldScale() const
{
	glm::vec2 scale;
	scale.x = glm::length(glm::vec2(transform.world[0]));
	scale.y = glm::length(glm::vec2(transform.world[1]));
	return scale;
}

void UIElement::SetWorldPosition(glm::vec2 position)
{
	if (parent)
	{
		GetRoot()->UpdateTransform();

		glm::mat4 invParent = glm::inverse(parent->transform.world);
		glm::vec4 local = invParent * glm::vec4(position, 0.0f, 1.0f);
		transform.position = glm::vec2(local);
	}
	else
	{
		transform.position = position;
	}
	SetDirty();
}

void UIElement::SetWorldRotate(float rotate)
{
	if (parent)
	{
		GetRoot()->UpdateTransform();

		float parentRot = parent->GetWorldRotate();
		transform.rotate = rotate - parentRot;
	}
	else
	{
		transform.rotate = rotate;
	}
	SetDirty();
}

void UIElement::SetWorldScale(glm::vec2 scale)
{
	if (parent)
	{
		GetRoot()->UpdateTransform();

		glm::vec2 parentScale = parent->GetWorldScale();
		if (parentScale.x == 0) parentScale.x = 0.0001f;
		if (parentScale.y == 0) parentScale.y = 0.0001f;
		transform.scale = scale / parentScale;
	}
	else
	{
		transform.scale = scale;
	}
	SetDirty();
}

UIElement* UIElement::GetRoot()
{
	UIElement* current = this;

	while (current->parent)
	{
		current = current->parent;
	}

	return current;
}

void UIElement::SetDirty()
{
	isDirty = true;

	for (UIElement* child : children)
	{
		child->SetDirty();
	}
}

UIElement::~UIElement()
{
	for (UIElement* child : children)
	{
		child->SetParent(parent);
	}
}

void UIElement::Destroy()
{
	if (!isPendingDestroy)
	{
		isPendingDestroy = true;
		if (scene)
		{
			scene->RegisterToDestroy(this);
		}
	}
}