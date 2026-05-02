#include "MainMenu/MainMenuScene.h"
#include "UI/Text.h"
#include "MainMenu/StartButton.h"

void MainMenuScene::CreateScene()
{
    Text* text = CreateUIElement<Text>("default");
    text->SetContent("JRPG_BattleSystem");
    text->SetWorldPosition(glm::vec2(320, 140));
    text->SetSize(36);

    StartButton* button = CreateUIElement<StartButton>("button", "default");
    button->SetWorldPosition(glm::vec2(320, 340));
    button->SetSize(glm::vec2(75, 50));

    Text* buttonText = CreateUIElement<Text>("default");
    buttonText->SetParent(button);
    buttonText->SetLocalPosition(glm::vec2(0, 0));
    buttonText->SetContent("Start");
    buttonText->SetSize(24);
}