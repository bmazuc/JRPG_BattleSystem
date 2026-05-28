#ifndef __SPATIAL_NODE_H_INCLUDED__
#define __SPATIAL_NODE_H_INCLUDED__

#include "Core/Math/Transform2D.h"
#include "Rendering/RenderQueue.h"

#include <vector>

class ISpatialNodeOwner;
class SpatialGraph;
class ISpatialNodeOrderProvider;

/**
 * Node in a hierarchical transform tree.
 * Each node can have a parent and multiple children.
 * It stores local transform data and computes world transform based on hierarchy.
 */
class SpatialNode
{
public:
	/**
	 * Recomputes world transform if the node is marked dirty.
	 * Propagates update to children nodes.
	 */
	void UpdateTransform();

	void BuildRenderQueue(RenderQueue& queue, ISpatialNodeOrderProvider* provider);

	SpatialNode* GetParent() { return parent; }
	const SpatialNode* GetParent() const { return parent; }

	/**
	 * Sets the parent of this node.
	 */
	bool SetParent(SpatialNode* _parent);

	/**
	 * Returns true if this node has a parent.
	 */
	bool HasParent() const { return parent; }

	std::vector<SpatialNode*> GetChildren() { return children; }
	const std::vector<SpatialNode*> GetChildren() const { return children; }

	/**
	 * Detaches this node from its parent and children and clears hierarchy links.
	 */
	void DetachFromHierarchy();

	/**
	 * Synchronize the graph with the current state of this node
	 */
	void SyncGraph(SpatialGraph* graph);

	/**
	 * Transform accessors
	 */

	Transform2D& GetTransform() { return transform; }
	const Transform2D& GetTransform() const { return transform; }

	glm::vec2 GetWorldPosition() const;
	float GetWorldRotate() const;
	glm::vec2 GetWorldScale() const;

	void SetWorldPosition(glm::vec2 position);
	void SetWorldRotate(float rotate);
	void SetWorldScale(glm::vec2 scale);

	glm::vec2 GetLocalPosition() const { return transform.position; }
	float GetLocalRotate() const { return transform.rotate; }
	glm::vec2 GetLocalScale() const { return transform.scale; }

	void SetLocalPosition(glm::vec2 position);
	void SetLocalRotate(float rotate);
	void SetLocalScale(glm::vec2 scale);

	ISpatialNodeOwner* GetOwner() { return owner; }
	const ISpatialNodeOwner* GetOwner() const { return owner; }

	void SetOwner(ISpatialNodeOwner* newOwner) { owner = newOwner; }

	/**
	 * Returns the root node of this hierarchy.
	 */
	SpatialNode* GetRoot();
	const SpatialNode* GetRoot() const;

	bool IsHierarchyDirty() const { return isHierarchyDirty; }

	void MarkChildrenDirty() { isChildrenDirty = true; }

private:
	/**
	 * Adds a child node to this node.
	 */
	void AddChild(SpatialNode* node);

	/**
	 * Removes a child node from this node.
	 */
	void RemoveChild(SpatialNode* node);

	/**
	 * Returns true if this node is an ancestor of the given node.
	 */
	bool IsAncestorOf(SpatialNode* node);

	/**
	 * Marks this node as dirty, forcing transform recomputation.
	 */
	void MarkTransformDirty();

	/**
	 * Marks this node as dirty, forcing hierarchy recomputation.
	 */
	void MarkHierarchyDirty() { isHierarchyDirty = true; }

	void SortChildrenIfNeeded(ISpatialNodeOrderProvider* provider);

	Transform2D transform;

	SpatialNode* parent = nullptr;
	std::vector<SpatialNode*> children;

	// Indicates whether the world transform needs recomputation.
	bool isTransformDirty = true;

	// Indicates whether the node should be moved inside the hierarchy.
	bool isHierarchyDirty = true;

	bool isChildrenDirty = false;

	bool wasRoot = false;

	ISpatialNodeOwner* owner;
};

#endif // __SPATIAL_NODE_H_INCLUDED__