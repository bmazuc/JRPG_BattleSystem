#include "World/SpatialGraph/SpatialNode.h"
#include "Rendering/IRenderable.h"
#include "World/SpatialGraph/ISpatialNodeOwner.h"
#include "World/SpatialGraph/SpatialGraph.h"
#include "World/SpatialGraph/ISpatialNodeOrderProvider.h"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>
#include <SDL3/SDL.h>

void SpatialNode::UpdateTransform()
{
	if (isTransformDirty)
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

		isTransformDirty = false;
	}

	for (SpatialNode* child : children)
	{
		child->UpdateTransform();
	}
}

void SpatialNode::SyncGraph(SpatialGraph* graph)
{
	if (isHierarchyDirty && graph) 
	{
		bool isRoot = (parent == nullptr);

		if (isRoot && !wasRoot)
		{
			graph->AddNode(this);
		}
		else if (!isRoot && wasRoot)
		{
			graph->RemoveNode(this);
		}

		wasRoot = isRoot;
		isHierarchyDirty = false;
	}
}

void SpatialNode::BuildRenderQueue(RenderQueue& queue, ISpatialNodeOrderProvider* provider)
{
	SortChildrenIfNeeded(provider);

	if (IRenderable* renderable = dynamic_cast<IRenderable*>(GetOwner()))
	{
		renderable->AddToRenderQueue(queue);
	}

	for (SpatialNode* child : children)
	{
		if (child)
		{
			child->BuildRenderQueue(queue, provider);
		}
	}
}

void SpatialNode::SortChildrenIfNeeded(ISpatialNodeOrderProvider* provider)
{
	if (!isChildrenDirty || !provider)
	{
		return;
	}

	std::stable_sort(children.begin(), children.end(),
		[&](SpatialNode* a, SpatialNode* b)
		{
			return provider->Less(a, b);
		});

	isChildrenDirty = false;
}

bool SpatialNode::SetParent(SpatialNode* _parent)
{
	if (parent != _parent)
	{
		if (_parent && _parent->IsAncestorOf(this))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot attach parent to one of its children.");
			return false;
		}

		wasRoot = (parent == nullptr);

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

		return true;
	}

	return false;
}

void SpatialNode::AddChild(SpatialNode* child)
{
	children.push_back(child);
	MarkChildrenDirty();
}

void SpatialNode::RemoveChild(SpatialNode* child)
{
	children.erase(std::remove(children.begin(), children.end(), child), children.end());
	MarkChildrenDirty();
}

bool SpatialNode::IsAncestorOf(SpatialNode* node)
{
	if (this == node)
	{
		return true;
	}

	for (SpatialNode* child : children)
	{
		if (child->IsAncestorOf(node))
		{
			return true;
		}
	}

	return false;
}

SpatialNode* SpatialNode::GetRoot()
{
	SpatialNode* current = this;

	while (current->parent)
	{
		current = current->parent;
	}

	return current;
}

const SpatialNode* SpatialNode::GetRoot() const
{
	const SpatialNode* current = this;

	while (current->parent)
	{
		current = current->parent;
	}

	return current;
}

void SpatialNode::MarkTransformDirty()
{
	isTransformDirty = true;

	for (SpatialNode* child : children)
	{
		child->MarkTransformDirty();
	}
}

void SpatialNode::DetachFromHierarchy()
{
	if (parent)
	{
		parent->RemoveChild(this);
	}

	std::vector<SpatialNode*> pendingChildren = children;
	for (SpatialNode* child : pendingChildren)
	{
		child->SetParent(nullptr);
	}
}

void SpatialNode::SetLocalPosition(glm::vec2 position)
{
	transform.position = position;
	MarkTransformDirty();
}

void SpatialNode::SetLocalRotate(float rotate)
{
	transform.rotate = rotate;
	MarkTransformDirty();
}

void SpatialNode::SetLocalScale(glm::vec2 scale)
{
	transform.scale = scale;
	MarkTransformDirty();
}

glm::vec2 SpatialNode::GetWorldPosition() const
{
	return glm::vec2(transform.world[3]);
}

float SpatialNode::GetWorldRotate() const
{
	return glm::degrees(atan2(transform.world[1][0], transform.world[0][0]));
}

glm::vec2 SpatialNode::GetWorldScale() const
{
	glm::vec2 scale;
	scale.x = glm::length(glm::vec2(transform.world[0]));
	scale.y = glm::length(glm::vec2(transform.world[1]));
	return scale;
}

void SpatialNode::SetWorldPosition(glm::vec2 position)
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
	MarkTransformDirty();
}

void SpatialNode::SetWorldRotate(float rotate)
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
	MarkTransformDirty();
}

void SpatialNode::SetWorldScale(glm::vec2 scale)
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
	MarkTransformDirty();
}