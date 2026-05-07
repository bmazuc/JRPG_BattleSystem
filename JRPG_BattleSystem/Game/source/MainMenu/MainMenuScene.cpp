#include "MainMenu/MainMenuScene.h"
#include "UI/Text.h"
#include "Common/UI/LoadSceneButton.h"
#include "Rendering/Material.h"
#include "Core/Resource/ResourceManager.h"

void MainMenuScene::LoadAssets()
{
    ResourceManager::LoadPNGTexture("Assets/button.png", "button");
}

void MainMenuScene::CreateScene()
{
    Text* text = CreateUIElement<Text>("Title", glm::vec2(320, 140), 0, glm::vec2(1, 1));
    text->SetContent("JRPG_BattleSystem");
    text->SetSize(36);

    CreateLoadSceneButton(glm::vec2(320, 300), glm::vec2(75, 50),
        "battleScene",
        "Battle", 24);

    CreateLoadSceneButton(glm::vec2(320, 400), glm::vec2(75, 50),
        "testScene",
        "Test", 24);
}

void MainMenuScene::CreateLoadSceneButton(glm::vec2 position, glm::vec2 buttonSize, std::string sceneToLoad, std::string content, int textSize)
{
    LoadSceneButton* button = CreateUIElement<LoadSceneButton>(sceneToLoad + "Button", position, 0, glm::vec2(1, 1));
    button->GetMaterial()->SetTexture("button");
    button->SetSize(buttonSize);
    button->SetSceneToLoad(sceneToLoad);

    Text* buttonText = CreateUIElement<Text>(sceneToLoad + "ButtonText", button, glm::vec2(0, 0), 0, glm::vec2(1, 1));
    buttonText->SetContent(content);
    buttonText->SetSize(textSize);
}