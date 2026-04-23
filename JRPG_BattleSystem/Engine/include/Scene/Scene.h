#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

class CameraComponent;

#include "Actor.h"

class Scene
{
public:
	~Scene();

	void Init();
	void Update(float deltaTime);

	void AddGameObject(Actor* gameObject);

	CameraComponent* GetActiveCamera() { return activeCamera; }
	void SetActiveCamera(CameraComponent* camera) { activeCamera = camera; }
	std::vector<Actor*> GetGameObjects() const { return gameObjects; }

private:
	std::vector<Actor*> gameObjects;
	CameraComponent* activeCamera;
};

#endif // __SCENE_H_INCLUDED__