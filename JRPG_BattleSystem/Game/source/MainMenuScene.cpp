#include "MainMenuScene.h"
#include "ChangeSceneTimer.h"

void MainMenuScene::CreateScene()
{
    ChangeSceneTimer* timer = CreateUIElement<ChangeSceneTimer>("default");
    timer->SetWorldPosition(glm::vec2(320, 240));
    timer->SetSize(24);
}