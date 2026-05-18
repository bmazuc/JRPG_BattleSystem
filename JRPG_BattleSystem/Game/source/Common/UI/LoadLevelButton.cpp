#include "Common/UI/LoadLevelButton.h"
#include "World/World.h"

void LoadLevelButton::OnClicked()
{
	World::RequestLevelChange(levelToLoad);
}
