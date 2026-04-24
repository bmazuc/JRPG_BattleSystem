#include "Scene/Scene.h"
#include "Components/Component.h"

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

void Scene::UpdateTransforms()
{
	for (Actor* gameObject : gameObjects)
	{
		if (gameObject)
		{
			if (!gameObject->GetRoot()->HasParent())
			{
				gameObject->UpdateTransforms();
			}
		}
	}
}

void Scene::Update(float deltaTime)
{
	for (Actor* gameObject : gameObjects)
	{
		if (gameObject)
		{
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