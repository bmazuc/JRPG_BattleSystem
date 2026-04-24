#include "Components/Component.h"
#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

void Component::UpdateTransform()
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

	for (auto* c : children)
		c->UpdateTransform();
}

void Component::SetParent(Component* _parent)
{
	if (parent != _parent)
	{
		if (_parent->IsAncestorOf(this))
		{ 
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot attach parent to one of its children.");
			return;
		}

		if (parent)
		{
			parent->RemoveChild(this);
		}

		parent = _parent;

		if (parent)
		{
			parent->AddChild(this);
		}
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

	for (auto* c : children)
	{
		if (c->IsAncestorOf(component))
		{
			return true;
		}
	}

	return false;
}