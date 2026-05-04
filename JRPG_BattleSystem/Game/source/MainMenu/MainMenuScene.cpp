#include "MainMenu/MainMenuScene.h"
#include "UI/Text.h"
#include "MainMenu/StartButton.h"
#include "Rendering/Material.h"

void MainMenuScene::CreateScene()
{
    Text* text = CreateUIElement<Text>("Title", glm::vec2(320, 140), 0, glm::vec2(1, 1));
    text->SetContent("JRPG_BattleSystem");
    text->SetSize(36);

    StartButton* button = CreateUIElement<StartButton>("Button", glm::vec2(320, 340), 0, glm::vec2(1, 1));
    button->GetMaterial()->SetTexture("button");
    button->SetSize(glm::vec2(75, 50));

    Text* buttonText = CreateUIElement<Text>("ButtonText", button, glm::vec2(0, 0), 0, glm::vec2(1, 1));
    buttonText->SetContent("Start");
    buttonText->SetSize(24);
}