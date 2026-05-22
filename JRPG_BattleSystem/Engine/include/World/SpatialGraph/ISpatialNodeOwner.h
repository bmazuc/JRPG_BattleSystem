#ifndef __SPATIAL_NODE_OWNER_H_INCLUDED__
#define __SPATIAL_NODE_OWNER_H_INCLUDED__

#include "Core/Math/Transform2D.h"

class SpatialNode;
class SpatialGraph;

/**
 * Interface defining ownership over a SpatialNode.
 * Used to abstract components and widgets that participate in the level graph hierarchy.
 */
class ISpatialNodeOwner
{
public:
    virtual ~ISpatialNodeOwner() = default;

	/**
	 * Returns the SpatialNode owned by this object.
	 */
	virtual SpatialNode* GetNode() = 0;

	/**
	 * Returns true if the node has a parent in the hierarchy.
	 */
	virtual bool HasParent() = 0;

	/**
	 * Recomputes transform hierarchy (world transform update).
	 */
	virtual void UpdateTransform() = 0;
	
	/**
	 * Detaches this node from its parent hierarchy.
	 */
	virtual void DetachFromHierarchy() = 0;

	/**
	 * Transform access
	 */

	virtual Transform2D& GetTransform() = 0;
	virtual const Transform2D& GetTransform() const = 0;

	/**
	 * World-space transform
	 */

	virtual glm::vec2 GetWorldPosition() const = 0;
	virtual float GetWorldRotate() const = 0;
	virtual glm::vec2 GetWorldScale() const = 0;

	virtual void SetWorldPosition(glm::vec2 position) = 0;
	virtual void SetWorldRotate(float rotate) = 0;
	virtual void SetWorldScale(glm::vec2 scale) = 0;

	/**
	 * Local-space transform
	 */

	virtual glm::vec2 GetLocalPosition() const = 0;
	virtual float GetLocalRotate() const = 0;
	virtual glm::vec2 GetLocalScale() const = 0;

	virtual void SetLocalPosition(glm::vec2 position) = 0;
	virtual void SetLocalRotate(float rotate) = 0;
	virtual void SetLocalScale(glm::vec2 scale) = 0;
};

#endif // __SPATIAL_NODE_OWNER_H_INCLUDED__