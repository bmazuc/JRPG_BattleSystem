#ifndef __UI_ELEMENT_H_INCLUDED__
#define __UI_ELEMENT_H_INCLUDED__

#include "Scene/Object.h"
#include "Scene/SceneGraph/ISceneNodeOwner.h"
#include "Core/Math/Transform2D.h"
#include <string>

class Scene;

/**
 * Base class for all UI element in the engine.
 *
 * Widget represents a 2D interface object that:
 * - exists in the scene hierarchy
 * - has a transform (position / rotation / scale)
 * - can be parented to other widgets
 * - participates in update + rendering pipeline
 *
 * It is the UI equivalent of an Actor in world space.
 */
class Widget : public Object, public ISceneNodeOwner
{
public:
	Widget();
	virtual ~Widget() {};

	/**
	 * Updates the transform hierarchy (world/local propagation).
	 */
	void UpdateTransform();

	/**
	 * Detaches this element from its parent in the UI hierarchy.
	 */
	void DetachFromHierarchy();

	/**
	 * Called before object destruction.
	 */
	void BeginDestroy() override;

	/**
	 * Marks this widget for destruction.
	 * Also marks its children hierarchy for destruction.
	 */
	void MarkForDestruction();

	/**
	 * Scene graph integration
	 */

	SceneNode* GetSceneNode() { return &node; }

	bool HasParent() { return node.HasParent(); }

	Widget* GetParent();
	const Widget* GetParent() const;

	void SetParent(Widget* element);

	std::vector<Widget*> GetChildren();

	/*
	 *	Transform accessor
	 */

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

	/**
	 * Returns world transform matrix (used for rendering).
	 */
	glm::mat4 GetWorld() { return node.GetTransform().world; }

	/**
	 * Hierarchy root access
	 */

	Widget* GetRoot();
	const Widget* GetRoot() const;

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }
	void SetScene(Scene* newScene);

	void SetVisible(bool state) { isVisible = state; }
	bool IsVisible() const { return isVisible; }

protected:
	// Scene owning this widget
	Scene* scene;

private:
	SceneNode node;

	bool isVisible = true;
};

#endif // __UI_ELEMENT_H_INCLUDED__