#include "Scene/Scene.h"

void Scene::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

Scene::~Scene()
{
	for (GameObject* gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();
}