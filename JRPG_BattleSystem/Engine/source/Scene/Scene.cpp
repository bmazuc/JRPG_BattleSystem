#include "Scene/Scene.h"
#include "Components/Component.h"
#include "Components/Camera/CameraComponent.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <UI/Image.h>

#include "Graphics/Texture.h"
#include "Rendering/Shader.h"

void Scene::Init()
{
	for (Actor* actor : actors)
	{
		if (actor)
		{
			actor->Init();
		}
	}

	for (UIElement* uiElement : uiElements)
	{
		if (uiElement)
		{
			uiElement->Init();
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

	for (UIElement* element : uiElements)
	{
		if (element)
		{
			if (!element->GetRoot()->HasParent())
			{
				element->UpdateTransform();
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

	for (UIElement* uiElement : uiElements)
	{
		if (uiElement)
		{
			uiElement->Update(deltaTime);
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

	for (UIElement* uiElementToDestroy : uiElementsToDestroy)
	{
		if (uiElementToDestroy)
		{
			uiElements.erase(std::remove(uiElements.begin(), uiElements.end(), uiElementToDestroy), uiElements.end());
			delete uiElementToDestroy;
		}
	}

	uiElementsToDestroy.clear();
}

void Scene::DestroyScene()
{
	pendingRequest.type = SceneRequestType::None;
	pendingRequest.newSceneName = "";

	for (Actor* actor : actors)
	{
		delete actor;
	}

	actors.clear();

	for (UIElement* uiElement : uiElements)
	{
		delete uiElement;
	}

	uiElements.clear();
}

void Scene::RegisterToDestroy(Actor* actor)
{
	actorsToDestroy.push_back(actor);
}

void Scene::RegisterToDestroy(UIElement* uiElement)
{
	uiElementsToDestroy.push_back(uiElement);
}

void Scene::RequestSceneChange(std::string sceneName)
{
	pendingRequest.type = SceneRequestType::ChangeScene;
	pendingRequest.newSceneName = sceneName;
}