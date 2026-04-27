#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

class CameraComponent;

#include "Actor.h"
#include "UI/UIElement.h"

class Scene
{
public:
	~Scene();

	void Init();

	void UpdateTransforms();
	void Update(float deltaTime);
	void ProcessDestroy();

	CameraComponent* GetActiveCamera() { return activeCamera; }
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }
	std::vector<Actor*> GetActors() const { return actors; }
	std::vector<UIElement*> GetUIElements() const { return uiElements; }

	template<typename T, typename... Args>
	T* CreateActors(Args&&... args)
	{
		static_assert(std::is_base_of<Actor, T>::value, "T must inherit Actor");

		T* actor = new T(std::forward<Args>(args)...);
		actor->SetScene(this);
		actors.push_back(actor);

		return actor;
	}

	template<typename T, typename... Args>
	T* CreateUIElement(Args&&... args)
	{
		static_assert(std::is_base_of<UIElement, T>::value, "T must inherit UIElement");

		T* element = new T(std::forward<Args>(args)...);
		element->SetScene(this);
		uiElements.push_back(element);

		return element;
	}

	void RegisterToDestroy(Actor* actor);
	void RegisterToDestroy(UIElement* uiElement);

private:
	std::vector<Actor*> actors;
	std::vector<Actor*> actorsToDestroy;

	CameraComponent* activeCamera;

	std::vector<UIElement*> uiElements;
	std::vector<UIElement*> uiElementsToDestroy;
};

#endif // __SCENE_H_INCLUDED__