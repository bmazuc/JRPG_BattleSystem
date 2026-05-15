#include "Scene/Scene.h"
#include "Components/ActorComponent.h"
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

SpawnInfo::~SpawnInfo() {}

void Scene::Load()
{
	CreateScene();
}

void Scene::BeginPlay()
{
	playerController = new PlayerController();

	graph.UpdateTransforms();

	actorsCollection.BeginPlay();
	widgetsCollection.Construct();
	sceneSubsystemCollection.BeginPlay();

	actorsCollection.SetupInputs(playerController);
}

void Scene::Update(float deltaTime, InputManager* inputManager)
{
	// Update SceneGraph
	graph.UpdateTransforms();

	// Update inputs
	UpdateUIInputs(inputManager);
	playerController->UpdateInputs(inputManager);

	// Update objects
	actorsCollection.Update(deltaTime);
	widgetsCollection.Update(deltaTime);
	sceneSubsystemCollection.Update(deltaTime);

	// Process destruction and adding
	actorsCollection.ProcessDestroy();
	actorsCollection.ProcessComponentsDestroy();
	widgetsCollection.ProcessDestroy();
	sceneSubsystemCollection.ProcessDestroy();

	actorsCollection.ProcessAdd();
	actorsCollection.ProcessComponentsAdd();
	widgetsCollection.ProcessAdd();
	sceneSubsystemCollection.ProcessAdd();
}

void Scene::UpdateUIInputs(InputManager* inputManager)
{
	glm::vec2 mouse = inputManager->GetMousePosition();

	for (Widget* element : widgetsCollection.GetCollection())
	{
		Button* button = dynamic_cast<Button*>(element);
		if (button && button->IsVisible())
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
}

void Scene::Unload()
{
	pendingRequest.type = SceneRequestType::None;
	pendingRequest.newSceneName = "";

	graph.Clear();

	actorsCollection.Clear();
	widgetsCollection.Clear();
	sceneSubsystemCollection.Clear();

	delete playerController;
	playerController = nullptr;
}

void Scene::RegisterToDestroy(Actor* actor)
{
	actorsCollection.RegisterToDestroy(actor);
}

void Scene::RegisterToDestroy(Widget* widget)
{
	widgetsCollection.RegisterToDestroy(widget);
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

void Scene::InternalSpawnActor(Actor* actor,std::string name, const ActorSpawnInfo& spawnInfo)
{
	actor->SetName(name);
	actor->AttachToActor(spawnInfo.parent);
	actor->SetScene(this);

	if (spawnInfo.transformSpace == TransformSpace::World)
	{
		actor->SetWorldPosition(spawnInfo.location);
		actor->SetWorldRotate(spawnInfo.rotate);
		actor->SetWorldScale(spawnInfo.scale);
	}
	else
	{
		actor->SetLocalPosition(spawnInfo.location);
		actor->SetLocalRotate(spawnInfo.rotate);
		actor->SetLocalScale(spawnInfo.scale);
	}
	actorsCollection.Add(actor);
}

void Scene::InternalSpawnUserWidget(UserWidget* userWidget, std::string name, const UISpawnInfo& spawnInfo)
{
	userWidget->SetName(name);
	userWidget->SetParent(spawnInfo.parent);
	userWidget->SetScene(this);

	if (spawnInfo.transformSpace == TransformSpace::World)
	{
		userWidget->SetWorldPosition(spawnInfo.location);
		userWidget->SetWorldRotate(spawnInfo.rotate);
		userWidget->SetWorldScale(spawnInfo.scale);
	}
	else
	{
		userWidget->SetLocalPosition(spawnInfo.location);
		userWidget->SetLocalRotate(spawnInfo.rotate);
		userWidget->SetLocalScale(spawnInfo.scale);
	}
	widgetsCollection.Add(userWidget);
}