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

SpawnInfo::~SpawnInfo() {}

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