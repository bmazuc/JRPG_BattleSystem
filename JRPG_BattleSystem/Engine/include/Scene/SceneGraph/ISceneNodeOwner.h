#ifndef __SCENE_NODE_OWNER_H_INCLUDED__
#define __SCENE_NODE_OWNER_H_INCLUDED__


#include "Core/Math/Transform2D.h"
#include "Scene/SceneGraph/SceneNode.h"

class ISceneNodeOwner
{
public:
    virtual ~ISceneNodeOwner() = default;

	virtual SceneNode* GetSceneNode() = 0;

	virtual bool HasParent() = 0;

	virtual void UpdateTransform() = 0;
	virtual void DetachFromHierarchy() = 0;

	virtual Transform2D& GetTransform() = 0;
	virtual const Transform2D& GetTransform() const = 0;

	virtual glm::vec2 GetWorldPosition() const = 0;
	virtual float GetWorldRotate() const = 0;
	virtual glm::vec2 GetWorldScale() const = 0;

	virtual void SetWorldPosition(glm::vec2 position) = 0;
	virtual void SetWorldRotate(float rotate) = 0;
	virtual void SetWorldScale(glm::vec2 scale) = 0;

	virtual glm::vec2 GetLocalPosition() const = 0;
	virtual float GetLocalRotate() const = 0;
	virtual glm::vec2 GetLocalScale() const = 0;

	virtual void SetLocalPosition(glm::vec2 position) = 0;
	virtual void SetLocalRotate(float rotate) = 0;
	virtual void SetLocalScale(glm::vec2 scale) = 0;
};

#endif // __SCENE_NODE_OWNER_H_INCLUDED__