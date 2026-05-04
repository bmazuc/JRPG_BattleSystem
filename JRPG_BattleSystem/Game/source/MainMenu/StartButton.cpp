#include "MainMenu/StartButton.h"
#include "Scene/Scene.h"

void StartButton::OnClicked()
{
	GetScene()->RequestSceneChange("battleScene");
}