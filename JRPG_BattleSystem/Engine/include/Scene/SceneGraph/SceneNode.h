#ifndef __SCENE_NODE_H_INCLUDED__
#define __SCENE_NODE_H_INCLUDED__

#include "Core/Math/Transform2D.h"
#include <vector>

class ISceneNodeOwner;

/**
 * Node in a hierarchical transform tree.
 * Each node can have a parent and multiple children.
 * It stores local transform data and computes world transform based on hierarchy.
 */
class SceneNode
{
public:
	/**
	 * Recomputes world transform if the node is marked dirty.
	 * Propagates update to children nodes.
	 */
	void UpdateTransform();

	SceneNode* GetParent() { return parent; }
	const SceneNode* GetParent() const { return parent; }

	/**
	 * Sets the parent of this node.
	 */
	void SetParent(SceneNode* _parent);

	/**
	 * Returns true if this node has a parent.
	 */
	bool HasParent() const { return parent; }

	std::vector<SceneNode*> GetChildren() { return children; }
	const std::vector<SceneNode*> GetChildren() const { return children; }

	/**
	 * Detaches this node from its parent and children and clears hierarchy links.
	 */
	void DetachFromHierarchy();

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

	ISceneNodeOwner* GetOwner() { return owner; }
	const ISceneNodeOwner* GetOwner() const { return owner; }

	void SetOwner(ISceneNodeOwner* newOwner) { owner = newOwner; }

private:
	/**
	 * Adds a child node to this node.
	 */
	void AddChild(SceneNode* node);

	/**
	 * Removes a child node from this node.
	 */
	void RemoveChild(SceneNode* node);

	/**
	 * Returns true if this node is an ancestor of the given node.
	 */
	bool IsAncestorOf(SceneNode* node);

	/**
	 * Returns the root node of this hierarchy.
	 */
	SceneNode* GetRoot();

	/**
	 * Marks this node as dirty, forcing transform recomputation.
	 */
	void SetDirty();

	Transform2D transform;

	SceneNode* parent = nullptr;
	std::vector<SceneNode*> children;

	// Indicates whether the world transform needs recomputation.
	bool isDirty = true;

	ISceneNodeOwner* owner;
};

#endif // __SCENE_NODE_H_INCLUDED__