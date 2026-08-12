#include "World/Systems/UISystem.h"
#include "Core/Inputs/InputManager.h"
#include "UI/Button.h"
#include "UI/UserWidget.h"
#include "Core/Engine.h"
#include "Core/Window.h"

#include <SDL3/SDL_mouse.h>

UISystem::~UISystem()
{
	graph.Clear();
	widgetsCollection.Clear();
}

void UISystem::OnLevelUnload()
{
	graph.Clear();
	widgetsCollection.Clear();
}

void UISystem::FlushPendingAdds()
{
	widgetsCollection.FlushPendingAdds();
}

void UISystem::SyncGraph()
{
	for (Widget* widget : dirtyWidgets)
	{
		widget->GetNode()->SyncGraph(&graph);
	}
	dirtyWidgets.clear();
}

void UISystem::UpdateTransform()
{
	graph.UpdateTransforms();
}

void UISystem::UpdateEffectiveVisibility()
{
	graph.UpdateEffectiveVisibility();
}

void UISystem::Construct()
{
	widgetsCollection.Construct();
}

void UISystem::UpdateInputs(InputManager* inputManager)
{
	const Engine* engine = Engine::Get();

	if (!engine)
	{
		return;
	}

	glm::vec2 mouse = inputManager->GetMousePosition();
	mouse = engine->GetWindow()->ScreenToViewport(mouse);

	for (Widget* element : widgetsCollection.GetCollection())
	{
		Button* button = dynamic_cast<Button*>(element);
		if (button && button->IsEffectivelyVisible())
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

void UISystem::Update(float deltaTime) 
{
	widgetsCollection.Update(deltaTime);
}

void UISystem::FlushPendingDestroys()
{
	widgetsCollection.FlushPendingDestroys();
}

void UISystem::RegisterToDestroy(Widget* widget)
{
	widgetsCollection.RegisterToDestroy(widget);
}

void UISystem::InternalSpawnUserWidget(UserWidget* userWidget, std::string name, const UISpawnInfo& spawnInfo)
{
	userWidget->SetName(name);
	userWidget->SetUISystem(this);
	userWidget->SetParent(spawnInfo.parent);
	
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

	widgetsCollection.RegisterToAdd(userWidget);
	RegisterDirtyWidget(userWidget);
}