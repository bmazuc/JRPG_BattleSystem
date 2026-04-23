#include "Scene/Scene.h"

void Scene::AddGameObject(Actor* gameObject)
{
	gameObjects.push_back(gameObject);
}

void Scene::Init()
{
	for (Actor* gameObject : gameObjects)
	{
		if (gameObject)
		{
			gameObject->Init();
		}
	}
}

void Scene::Update(float deltaTime)
{
	for (Actor* gameObject : gameObjects)
	{
		if (gameObject)
		{
			gameObject->UpdateTransforms();
			gameObject->Update(deltaTime);
			gameObject->UpdateComponents(deltaTime);
		}
	}
}

Scene::~Scene()
{
	for (Actor* gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();
}