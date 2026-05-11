#ifndef __UI_ELEMENT_H_INCLUDED__
#define __UI_ELEMENT_H_INCLUDED__

#include "Scene/SceneGraph/ISceneNodeOwner.h"
#include "Core/Math/Transform2D.h"
#include <string>

class Scene;

/*
 *	Base class for UI element.
 */
class UIElement : public ISceneNodeOwner
{
public:
	UIElement();
	virtual ~UIElement() {};

	/*
	 *	Behavior called after scene loading
	 */
	virtual void BeginPlay() {}
	/*
	 *	Behavior called each frame
	 */
	virtual void Update(float deltaTime) {}

	void UpdateTransform();
	void DetachFromHierarchy();

	/*
	 *	Mark a component for destroy
	 *	Future upgrade : Add a destroy with a timer
	 */
	void Destroy(bool destroyChildren = false);

	SceneNode* GetSceneNode() { return &node; }

	bool HasParent() { return node.HasParent(); }
	UIElement* GetParent();
	const UIElement* GetParent() const;
	void SetParent(UIElement* _parent);
	std::vector<UIElement*> GetChildren();

	/*
	 *	Transform getter/setter
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

	glm::mat4 GetWorld() { return node.GetTransform().world; }

	UIElement* GetRoot();
	const UIElement* GetRoot() const;

	Scene* GetScene() { return scene; }
	const Scene* GetScene() const { return scene; }
	void SetScene(Scene* newScene);

	void SetName(std::string newName) { name = newName; };
	std::string GetName() const { return name; }

private:
	// Name associated to this element. Useful to identify this element.
	std::string name = "";

	SceneNode node;

	// reference to the scene the element lives in
	Scene* scene;

	// Are element mark for destruction ?
	bool isPendingDestroy = false;
};

#endif // __UI_ELEMENT_H_INCLUDED__