#include "UI/UserWidget.h"
#include "World/Systems/UISystem.h"

#include <SDL3/SDL.h>

void UserWidget::InternalSpawnWidget(Widget* widget, std::string name, const UISpawnInfo& spawnInfo)
{
	widget->SetName(name);

	Widget* parent = this;
	if (spawnInfo.parent)
	{
		if (spawnInfo.parent->GetRoot() == this)
		{
			parent = spawnInfo.parent;
		}
		else
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Try to add widget with a parent from another UserWidget.");
		}
	}

	widget->SetUISystem(uiSystem);
	widget->SetParent(parent);

	if (spawnInfo.transformSpace == TransformSpace::World)
	{
		widget->SetWorldPosition(spawnInfo.location);
		widget->SetWorldRotate(spawnInfo.rotate);
		widget->SetWorldScale(spawnInfo.scale);
	}
	else
	{
		widget->SetLocalPosition(spawnInfo.location);
		widget->SetLocalRotate(spawnInfo.rotate);
		widget->SetLocalScale(spawnInfo.scale);
	}

	uiSystem->AddWidget(widget);
}