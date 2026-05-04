#include "Components/Component.h"
#include "Scene/Actor.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

void Component::UpdateTransform()
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

	for (Component* child : children)
	{
		child->UpdateTransform();
	}
}

void Component::SetParent(Component* _parent)
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

void Component::AddChild(Component* child)
{
	children.push_back(child);
}

void Component::RemoveChild(Component* child)
{
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

bool Component::IsAncestorOf(Component* component)
{
	if (this == component)
	{
		return true;
	}

	for (Component* child : children)
	{
		if (child->IsAncestorOf(component))
		{
			return true;
		}
	}

	return false;
}

glm::vec2 Component::GetLocalPosition() const
{ 
	return transform.position;
}

float Component::GetLocalRotate() const
{ 
	return transform.rotate; 
}

glm::vec2 Component::GetLocalScale() const
{ 
	return transform.scale; 
}

void Component::SetLocalPosition(glm::vec2 position)
{ 
	transform.position = position; 
	SetDirty();
}

void Component::SetLocalRotate(float rotate)
{ 
	transform.rotate = rotate; 
	SetDirty();
}

void Component::SetLocalScale(glm::vec2 scale)
{ 
	transform.scale = scale; 
	SetDirty();
}

glm::vec2 Component::GetWorldPosition() const
{
	return glm::vec2(transform.world[3]);
}

float Component::GetWorldRotate() const
{
	return glm::degrees(atan2(transform.world[1][0], transform.world[0][0]));
}

glm::vec2 Component::GetWorldScale() const
{
	glm::vec2 scale;
	scale.x = glm::length(glm::vec2(transform.world[0]));
	scale.y = glm::length(glm::vec2(transform.world[1]));
	return scale;
}

void Component::SetWorldPosition(glm::vec2 position)
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

void Component::SetWorldRotate(float rotate)
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

void Component::SetWorldScale(glm::vec2 scale)
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

Component* Component::GetRoot()
{
	Component* current = this;

	while (current->parent)
	{
		current = current->parent;
	}

	return current;
}

void Component::SetDirty()
{
	isDirty = true;

	for (Component* child : children)
	{
		child->SetDirty();
	}
}

void Component::DetachFromHierarchy()
{
	if (parent)
	{
		parent->RemoveChild(this);
	}

	for (Component* child : children)
	{
		child->SetParent(nullptr);
	}
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

