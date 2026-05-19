#ifndef __SCENE_COMPONENT_H_INCLUDED__
#define __SCENE_COMPONENT_H_INCLUDED__

#include "ActorComponent.h"
#include "World/SpatialGraph/ISpatialNodeOwner.h"

/**
 * Component that has a transform and supports attachment.
 */
class SceneComponent : public ActorComponent, public ISpatialNodeOwner
{
public:
	SceneComponent();

	/**
	 * Called before object destruction.
	 */
	void NativeBeginDestroy() final;

	bool HasParent() { return node.HasParent(); }
	void SetParent(SceneComponent* component);
	SceneComponent* GetParent();
	const SceneComponent* GetParent() const;
	std::vector<SceneComponent*> GetChildren();

	SpatialNode* GetSceneNode() { return &node; }

	void UpdateTransform();
	void DetachFromHierarchy();

	Transform2D& GetTransform() { return node.GetTransform(); }
	const Transform2D& GetTransform() const { return node.GetTransform(); }

	glm::vec2 GetWorldPosition() const { return node.GetWorldPosition(); }
	float GetWorldRotate() const { return node.GetWorldRotate(); }
	glm::vec2 GetWorldScale() const { return node.GetWorldScale(); }

	void SetWorldPosition(glm::vec2 position);
	void SetWorldRotate(float rotate);
	void SetWorldScale(glm::vec2 scale);

	glm::vec2 GetLocalPosition() const { return node.GetLocalPosition(); }
	float GetLocalRotate() const { return node.GetLocalRotate(); }
	glm::vec2 GetLocalScale() const { return node.GetLocalScale(); }

	void SetLocalPosition(glm::vec2 position);
	void SetLocalRotate(float rotate);
	void SetLocalScale(glm::vec2 scale);

private:
	SpatialNode node;
};

#endif // __SCENE_COMPONENT_H_INCLUDED__