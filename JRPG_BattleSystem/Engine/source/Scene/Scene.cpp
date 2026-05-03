#include "Scene/Scene.h"
#include "Components/Component.h"
#include "Components/Camera/CameraComponent.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"
#include "Scene/PlayerController.h"
#include "Core/Inputs/InputManager.h"
#include "UI/Button.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <UI/Image.h>

#include "Graphics/Texture.h"
#include "Rendering/Shader.h"
#include "Scene/Actor.h"
#include "UI/UIElement.h"

void Scene::Load()
{
	CreateScene();
	isLoaded = true;
}

void Scene::BeginPlay()
{
	playerController = new PlayerController();

	for (Actor* actor : actors)
	{
		if (actor)
		{
			actor->BeginPlay();
			actor->ComponentsBeginPlay();
			actor->SetupInputs(playerController);
		}
	}

	for (UIElement* uiElement : uiElements)
	{
		if (uiElement)
		{
			uiElement->BeginPlay();
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

void Scene::UpdateInputs(float deltaTime)
{
	for (Actor* actor : actors)
	{
		if (actor)
		{
			actor->UpdateInputs(deltaTime);
			actor->UpdateComponents(deltaTime);
		}
	}

	for (UIElement* uiElement : uiElements)
	{
		if (uiElement)
		{
			uiElement->UpdateInputs(deltaTime);
		}
	}
}

void Scene::UpdateInputs(InputManager* inputManager)
{
	glm::vec2 mouse = inputManager->GetMousePosition();

	for (UIElement* element : uiElements)
	{
		if (Button* button = dynamic_cast<Button*>(element))
		{
			bool hover = button->IsPointInside(mouse);

			if (hover)
			{
				button->OnHover();

				if (inputManager->IsMousePressed(SDL_BUTTON_LEFT))
				{
					button->OnClicked();
				}
			}
		}
	}

	playerController->UpdateInputs(inputManager);
}

void Scene::ProcessDestroy()
{
	for (Actor* actorToDestroy : actorsToDestroy)
	{
		if (actorToDestroy)
		{
			actorToDestroy->GetRoot()->DetachChidren();

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

void Scene::Unload()
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

	delete playerController;
	playerController = nullptr;

	isLoaded = false;
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

glm::vec2 Scene::ScreenToWorld(glm::vec2 screenPos)
{
	glm::vec2 worldPos = screenPos;

	if (activeCamera)
	{
		worldPos -= activeCamera->GetWorldPosition();
		worldPos /= activeCamera->GetZoom();
	}

	return worldPos;
}

void Scene::InternalAddActor(Actor* actor)
{
	actor->SetScene(this);
	actors.push_back(actor);

	if (isLoaded)
	{
		actor->BeginPlay();
	}
}

void Scene::InternalAddUIElement(UIElement* element)
{
	element->SetScene(this);
	uiElements.push_back(element);

	if (isLoaded)
	{
		element->BeginPlay();
	}
}