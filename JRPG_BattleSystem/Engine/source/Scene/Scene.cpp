#include "Scene/Scene.h"
#include "Components/Component.h"

void Scene::Init()
{
	for (Actor* gameObject : actors)
	{
		if (gameObject)
		{
			gameObject->Init();
		}
	}
}

void Scene::UpdateTransforms()
{
	for (Actor* actor : actors)
	{
		if (actor)
		{
			if (!actor->GetRoot()->HasParent())
			{
				actor->UpdateTransforms();
			}
		}
	}
}

void Scene::Update(float deltaTime)
{
	for (Actor* actor : actors)
	{
		if (actor)
		{
			actor->Update(deltaTime);
			actor->UpdateComponents(deltaTime);
		}
	}
}

void Scene::ProcessDestroy()
{
	for (Actor* actorToDestroy : actorsToDestroy)
	{
		if (actorToDestroy)
		{
			actors.erase(std::remove(actors.begin(), actors.end(), actorToDestroy), actors.end());
			delete actorToDestroy;
		}
	}

	actorsToDestroy.clear();

	for (Actor* actor : actors)
	{
		if (actor)
		{
			actor->ProcessComponentsDestroy();
		}
	}
}

Scene::~Scene()
{
	for (Actor* actor : actors)
	{
		delete actor;
	}

	actors.clear();
}

void Scene::RegisterToDestroy(Actor* actor)
{
	actorsToDestroy.push_back(actor);
}