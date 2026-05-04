#include "BattleScene/ReturnButton.h"
#include "Scene/Scene.h"

void ReturnButton::OnClicked()
{
	GetScene()->RequestSceneChange("mainMenu");
}