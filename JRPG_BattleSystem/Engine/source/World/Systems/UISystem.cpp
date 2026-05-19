#include "World/Systems/UISystem.h"
#include "Core/Inputs/InputManager.h"
#include "UI/Button.h"
#include "UI/UserWidget.h"

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

void UISystem::UpdateTransform()
{
	graph.UpdateTransforms();
}

void UISystem::UpdateInputs(InputManager* inputManager)
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
}