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
    mainMenuWidget = CreateUserWidget<UserWidget>("MainMenuWidget", UISpawnInfo());

    Text* text = mainMenuWidget->CreateWidget<Text>("Title", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 140)));
    text->SetContent("JRPG_BattleSystem");
    text->SetSize(36);

    CreateLoadSceneButton(glm::vec2(320, 300), glm::vec2(75, 50),
        "battleScene",
        "Battle", 24.0f);
}

void MainMenuScene::CreateLoadSceneButton(glm::vec2 position, glm::vec2 buttonSize, std::string sceneToLoad, std::string content, float textSize)
{
    if (mainMenuWidget)
    {
        LoadSceneButton* button = mainMenuWidget->CreateWidget<LoadSceneButton>(sceneToLoad + "Button", UISpawnInfo(nullptr, TransformSpace::World, position));
        button->GetMaterial()->SetTexture("button");
        button->SetSize(buttonSize);
        button->SetSceneToLoad(sceneToLoad);

        Text* buttonText = mainMenuWidget->CreateWidget<Text>(sceneToLoad + "ButtonText", UISpawnInfo(button, TransformSpace::Local));
        buttonText->SetContent(content);
        buttonText->SetSize(textSize);
    }
}