#include "Scene/SceneGraph/SceneNode.h"

#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

void SceneNode::UpdateTransform()
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

	for (SceneNode* child : children)
	{
		child->UpdateTransform();
	}
}

void SceneNode::SetParent(SceneNode* _parent)
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

void SceneNode::AddChild(SceneNode* child)
{
	children.push_back(child);
}

void SceneNode::RemoveChild(SceneNode* child)
{
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
}

bool SceneNode::IsAncestorOf(SceneNode* node)
{
	if (this == node)
	{
		return true;
	}

	for (SceneNode* child : children)
	{
		if (child->IsAncestorOf(node))
		{
			return true;
		}
	}

	return false;
}

SceneNode* SceneNode::GetRoot()
{
	SceneNode* current = this;

	while (current->parent)
	{
		current = current->parent;
	}

	return current;
}

void SceneNode::SetDirty()
{
	isDirty = true;

	for (SceneNode* child : children)
	{
		child->SetDirty();
	}
}

void SceneNode::DetachFromHierarchy()
{
	if (parent)
	{
		parent->RemoveChild(this);
	}

	for (SceneNode* child : children)
	{
		child->SetParent(nullptr);
	}
}

void SceneNode::SetLocalPosition(glm::vec2 position)
{
	transform.position = position;
	SetDirty();
}

void SceneNode::SetLocalRotate(float rotate)
{
	transform.rotate = rotate;
	SetDirty();
}

void SceneNode::SetLocalScale(glm::vec2 scale)
{
	transform.scale = scale;
	SetDirty();
}

glm::vec2 SceneNode::GetWorldPosition() const
{
	return glm::vec2(transform.world[3]);
}

float SceneNode::GetWorldRotate() const
{
	return glm::degrees(atan2(transform.world[1][0], transform.world[0][0]));
}

glm::vec2 SceneNode::GetWorldScale() const
{
	glm::vec2 scale;
	scale.x = glm::length(glm::vec2(transform.world[0]));
	scale.y = glm::length(glm::vec2(transform.world[1]));
	return scale;
}

void SceneNode::SetWorldPosition(glm::vec2 position)
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

void SceneNode::SetWorldRotate(float rotate)
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

void SceneNode::SetWorldScale(glm::vec2 scale)
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