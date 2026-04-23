#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

class CameraComponent;

#include "GameObject.h"

class Scene
{
public:
	~Scene();

	void Init();
	void Update(float deltaTime);

	void AddGameObject(GameObject* gameObject);

	CameraComponent* GetActiveCamera() { return activeCamera; }
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }
	std::vector<GameObject*> GetGameObjects() const { return gameObjects; }

private:
	std::vector<GameObject*> gameObjects;
	CameraComponent* activeCamera;
};

#endif // __SCENE_H_INCLUDED__