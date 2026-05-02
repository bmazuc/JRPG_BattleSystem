#ifndef __UI_ELEMENT_H_INCLUDED__
#define __UI_ELEMENT_H_INCLUDED__

#include "Core/Math/Transform2D.h"
#include <vector>

class Scene;

/*
 *	Base class for UI element.
 */
class UIElement
{
public:
	virtual ~UIElement();

	/*
	 *	Behavior called after scene loading
	 */
	virtual void Init() {}
	/*
	 *	Behavior called each frame
	 */
	virtual void UpdateInputs(float deltaTime) {}

	/*
	 *	If marked dirty, update this element transform.
	 *	Called UpdateTransform() on children.
	 */
	void UpdateTransform();

	/*
	 *	Mark a component for destroy
	 *	Future upgrade : Add a destroy with a timer
	 */
	void Destroy(bool destroyChildren = false);

	void AddChild(UIElement* child);
	void RemoveChild(UIElement* child);

	UIElement* GetParent() { return parent; }
	const UIElement* GetParent() const { return parent; }
	void SetParent(UIElement* _parent);
	bool HasParent() const { return parent; }

	/*
	 *	Transform getter/setter
	 */

	glm::vec2 GetWorldPosition() const;
	float GetWorldRotate() const;
	glm::vec2 GetWorldScale() const;

	void SetWorldPosition(glm::vec2 position);
	void SetWorldRotate(float rotate);
	void SetWorldScale(glm::vec2 scale);

	glm::vec2 GetLocalPosition() const;
	float GetLocalRotate() const;
	glm::vec2 GetLocalScale() const;

	void SetLocalPosition(glm::vec2 position);
	void SetLocalRotate(float rotate);
	void SetLocalScale(glm::vec2 scale);

	glm::mat4 GetWorld() { return transform.world; }

	UIElement* GetRoot();
	const UIElement* GetRoot() const;

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }
	void SetScene(Scene* _scene) { scene = _scene; }

private:
	// Mark this element as dirty
	void SetDirty();
	// Is this element an ancestor of the specified element ?
	bool IsAncestorOf(UIElement* element);

	Transform2D transform;

	// reference to the scene the element lives in
	Scene* scene;
	UIElement* parent = nullptr;
	std::vector<UIElement*> children;

	// Should this element update its transform ?
	bool isDirty = true;
	// Are element mark for destruction ?
	bool isPendingDestroy = false;
};

#endif // __UI_ELEMENT_H_INCLUDED__