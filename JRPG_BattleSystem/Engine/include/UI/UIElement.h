#ifndef __UI_ELEMENT_H_INCLUDED__
#define __UI_ELEMENT_H_INCLUDED__

#include "Transform2D.h"
#include <vector>

class Scene;

class UIElement
{
public:
	virtual ~UIElement();

	virtual void Init() {}
	virtual void Update(float deltaTime) {}

	void UpdateTransform();

	void AddChild(UIElement* child);
	void RemoveChild(UIElement* child);

	void SetParent(UIElement* _parent);
	bool HasParent() const { return parent; }

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

	Scene* GetScene() const { return scene; }
	void SetScene(Scene* _scene) { scene = _scene; }

	void Destroy();

private:
	void SetDirty();
	bool IsAncestorOf(UIElement* element);

	Transform2D transform;

	Scene* scene;
	UIElement* parent = nullptr;
	std::vector<UIElement*> children;

	bool isDirty = true;
	bool isPendingDestroy = false;
};

#endif // __UI_ELEMENT_H_INCLUDED__