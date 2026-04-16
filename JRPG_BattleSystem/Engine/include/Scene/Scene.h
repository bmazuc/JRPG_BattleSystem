#ifndef __SCENE_H_INCLUDED__
#define __SCENE_H_INCLUDED__

#include "GameObject.h"

class Scene
{
public:
	~Scene();

	void Init();
	void Update();

	void AddGameObject(GameObject* gameObject);

	std::vector<GameObject*> GetGameObjects() const { return gameObjects; }

private:
	std::vector<GameObject*> gameObjects;
};

#endif // __SCENE_H_INCLUDED__