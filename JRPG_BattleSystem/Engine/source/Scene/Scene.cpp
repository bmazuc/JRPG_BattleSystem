#include "Scene/Scene.h"

void Scene::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

void Scene::Init()
{
	for (GameObject* gameObject : gameObjects)
	{
		if (gameObject)
		{
			gameObject->Init();
		}
	}
}

void Scene::Update()
{
	for (GameObject* gameObject : gameObjects)
	{
		if (gameObject)
		{
			gameObject->Update();
		}
	}
}

Scene::~Scene()
{
	for (GameObject* gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();
}