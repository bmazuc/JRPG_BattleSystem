#ifndef __SCENE_NODE_H_INCLUDED__
#define __SCENE_NODE_H_INCLUDED__

#include "Core/Math/Transform2D.h"
#include <vector>

class ISceneNodeOwner;

class SceneNode
{
public:
	/*
	 *	If marked dirty, update this component transform.
     *	Called UpdateTransform() on children.
	 */
	void UpdateTransform();

	SceneNode* GetParent() { return parent; }
	const SceneNode* GetParent() const { return parent; }
	void SetParent(SceneNode* _parent);
	// Does this node have a parent ?
	bool HasParent() const { return parent; }

	std::vector<SceneNode*> GetChildren() { return children; }
	const std::vector<SceneNode*> GetChildren() const { return children; }

	// Detach all the children of this node from het and detach node from his parent.
	void DetachFromHierarchy();

	/*
	 *	Transform getter/setter
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
	void AddChild(SceneNode* node);
	void RemoveChild(SceneNode* node);
	// Is this node an ancestor of the specified SceneNode ?
	bool IsAncestorOf(SceneNode* node);

	SceneNode* GetRoot();

	// Mark this component as dirty
	void SetDirty();

	Transform2D transform;

	SceneNode* parent;
	std::vector<SceneNode*> children;
	// Should this component update its transform ?
	bool isDirty = true;

	ISceneNodeOwner* owner;
};

#endif // __SCENE_NODE_H_INCLUDED__