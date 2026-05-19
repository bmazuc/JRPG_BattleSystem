#include "MainMenu/MainMenuLevel.h"
#include "UI/Text.h"
#include "Common/UI/LoadLevelButton.h"
#include "Rendering/Material.h"
#include "Core/Resource/ResourceManager.h"
#include "World/World.h"
#include "World/Systems/UISystem.h"
#include "UI/UserWidget.h"

void MainMenuLevel::LoadAssets()
{
    ResourceManager::LoadPNGTexture("Assets/button.png", "button");
}

void MainMenuLevel::CreateLevel()
{
    UISystem* uiSystem = world->GetUISystem();

    mainMenuWidget = uiSystem->CreateUserWidget<UserWidget>("MainMenuWidget", UISpawnInfo());

    Text* text = mainMenuWidget->CreateWidget<Text>("Title", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(320, 140)));
    text->SetContent("JRPG_BattleSystem");
    text->SetSize(36);

    CreateLoadLevelButton(glm::vec2(320, 300), glm::vec2(75, 50),
        "battleLevel",
        "Battle", 24.0f);
}

void MainMenuLevel::CreateLoadLevelButton(glm::vec2 position, glm::vec2 buttonSize, std::string levelToLoad, std::string content, float textSize)
{
    if (mainMenuWidget)
    {
        LoadLevelButton* button = mainMenuWidget->CreateWidget<LoadLevelButton>(levelToLoad + "Button", UISpawnInfo(nullptr, TransformSpace::World, position));
        button->GetMaterial()->SetTexture("button");
        button->SetSize(buttonSize);
        button->SetLevelToLoad(levelToLoad);

        Text* buttonText = mainMenuWidget->CreateWidget<Text>(levelToLoad + "ButtonText", UISpawnInfo(button, TransformSpace::Local));
        buttonText->SetContent(content);
        buttonText->SetSize(textSize);
    }
}