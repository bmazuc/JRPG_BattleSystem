#include "Common/UI/LoadSceneButton.h"
#include "Scene/Scene.h"

void LoadSceneButton::OnClicked()
{
	GetScene()->RequestSceneChange(sceneToLoad);
}
