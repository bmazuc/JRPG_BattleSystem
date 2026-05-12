#ifndef __UI_ELEMENT_H_INCLUDED__
#define __UI_ELEMENT_H_INCLUDED__

#include "Scene/SceneGraph/ISceneNodeOwner.h"
#include "Core/Math/Transform2D.h"
#include <string>

class Scene;

/**
 * Base class for all UI elements in the engine.
 *
 * UIElement represents a 2D interface object that:
 * - exists in the scene hierarchy
 * - has a transform (position / rotation / scale)
 * - can be parented to other UI elements
 * - participates in update + rendering pipeline
 *
 * It is the UI equivalent of an Actor in world space.
 */
class UIElement : public ISceneNodeOwner
{
public:
	UIElement();
	virtual ~UIElement() {};

	/**
	 * Called once when the scene starts or element is created.
	 */
	virtual void BeginPlay() {}

	/**
	 * Called every frame for UI logic updates.
	 */
	virtual void Update(float deltaTime) {}

	/**
	 * Updates the transform hierarchy (world/local propagation).
	 */
	void UpdateTransform();

	/**
	 * Detaches this element from its parent in the UI hierarchy.
	 */
	void DetachFromHierarchy();

	/**
	 * Marks this UI element for destruction.
	 * If destroyChildren is true, also removes its children hierarchy.
	 */
	void Destroy(bool destroyChildren = false);

	/**
	 * Scene graph integration
	 */

	SceneNode* GetSceneNode() { return &node; }

	bool HasParent() { return node.HasParent(); }

	UIElement* GetParent();
	const UIElement* GetParent() const;

	void SetParent(UIElement* element);

	std::vector<UIElement*> GetChildren();

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

	UIElement* GetRoot();
	const UIElement* GetRoot() const;

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }
	void SetScene(Scene* newScene);

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

protected:
	// Scene owning this UI element
	Scene* scene;

private:
	// Identifier used for lookup.
	std::string name = "";

	SceneNode node;

	// Are this element mark for destruction ?
	bool isPendingDestroy = false;
};

#endif // __UI_ELEMENT_H_INCLUDED__