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
}

void Scene::BeginPlay()
{
	playerController = new PlayerController();
	actorsCollection.SetPlayerController(playerController);

	UpdateTransforms();

	actorsCollection.BeginPlay();
	uiElementsCollection.BeginPlay();
}

void Scene::UpdateTransforms()
{
	actorsCollection.UpdateTransforms();
	uiElementsCollection.UpdateTransforms();
}

void Scene::Update(float deltaTime)
{
	actorsCollection.Update(deltaTime);
	uiElementsCollection.Update(deltaTime);
}

void Scene::UpdateInputs(InputManager* inputManager)
{
	glm::vec2 mouse = inputManager->GetMousePosition();

	for (UIElement* element : uiElementsCollection.GetCollection())
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
	actorsCollection.ProcessDestroy();
	uiElementsCollection.ProcessDestroy();
}

void Scene::Unload()
{
	pendingRequest.type = SceneRequestType::None;
	pendingRequest.newSceneName = "";

	actorsCollection.Clear();
	uiElementsCollection.Clear();

	delete playerController;
	playerController = nullptr;
}

void Scene::RegisterToDestroy(Actor* actor)
{
	actorsCollection.RegisterToDestroy(actor);
}

void Scene::RegisterToDestroy(UIElement* uiElement)
{
	uiElementsCollection.RegisterToDestroy(uiElement);
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

void Scene::InternalAddActor(Actor* actor, std::string name, glm::vec2 worldLocation, float worldRotate, glm::vec2 worldScale)
{
	actor->SetName(name);
	actor->SetWorldPosition(worldLocation);
	actor->SetWorldRotate(worldRotate);
	actor->SetWorldScale(worldScale);
	
	actor->SetScene(this);

	actorsCollection.Add(actor);
}

void Scene::InternalAddActor(Actor* actor, Actor* parent, std::string name, glm::vec2 localLocation, float localRotate, glm::vec2 localScale)
{
	actor->SetName(name);
	actor->AttachToActor(parent);
	actor->SetLocalPosition(localLocation);
	actor->SetLocalRotate(localRotate);
	actor->SetLocalScale(localScale);

	actor->SetScene(this);

	actorsCollection.Add(actor);
}

void Scene::InternalAddUIElement(UIElement* element, std::string name, glm::vec2 worldLocation, float worldRotate, glm::vec2 worldScale)
{
	element->SetName(name);
	element->SetWorldPosition(worldLocation);
	element->SetWorldRotate(worldRotate);
	element->SetWorldScale(worldScale);

	element->SetScene(this);

	uiElementsCollection.Add(element);
}

void Scene::InternalAddUIElement(UIElement* element, UIElement* parent, std::string name, glm::vec2 localLocation, float localRotate, glm::vec2 localScale)
{
	element->SetName(name);
	element->SetParent(parent);
	element->SetLocalPosition(localLocation);
	element->SetLocalRotate(localRotate);
	element->SetLocalScale(localScale);

	element->SetScene(this);

	uiElementsCollection.Add(element);
}