#include "BattleScene/BattleScene.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "BattleScene/Enemy.h"
#include "Components/Camera/CameraComponent.h"
#include "Core/Resource/ResourceManager.h"
#include "UI/Text.h"
#include "BattleScene/ReturnButton.h"
#include "BattleScene/CrossButton.h"

void BattleScene::CreateScene()
{
    Text* goblinText = CreateUIElement<Text>("default");
    goblinText->SetWorldPosition(glm::vec2(320, 50));
    goblinText->SetContent("Click on the middle goblin to make them move.");
    goblinText->SetColor(glm::vec3(1, 0, 0));
    goblinText->SetSize(24);

    Text* crossText = CreateUIElement<Text>("default");
    crossText->SetWorldPosition(glm::vec2(320, 75));
    crossText->SetContent("Click on the cross to destroy its button.");
    crossText->SetColor(glm::vec3(1, 0, 0));
    crossText->SetSize(24);

    ReturnButton* mainMenuButton = CreateUIElement<ReturnButton>("button", "default");
    mainMenuButton->SetWorldPosition(glm::vec2(320, 390));
    mainMenuButton->SetSize(glm::vec2(150, 50));

    Text* mainMenuButtonText = CreateUIElement<Text>("default");
    mainMenuButtonText->SetParent(mainMenuButton);
    mainMenuButtonText->SetLocalPosition(glm::vec2(0, 0));
    mainMenuButtonText->SetContent("Main Menu");
    mainMenuButtonText->SetSize(24);

    CrossButton* crossButton = CreateUIElement<CrossButton>("button", "default");
    crossButton->SetWorldPosition(glm::vec2(40, 40));
    crossButton->SetSize(glm::vec2(30, 30));

    Text* crossButtonText = CreateUIElement<Text>("default");
    crossButtonText->SetParent(crossButton);
    crossButtonText->SetLocalPosition(glm::vec2(0, 0));
    crossButtonText->SetContent("X");
    crossButtonText->SetSize(24);

    Enemy* enemy = CreateActor<Enemy>("goblin", "default");
    enemy->SetWorldPosition(glm::vec2(320, 240));
    enemy->SetSpeed(50.0f);
    SpriteRendererComponent* enemySprite = enemy->GetSpriteRenderer();
    enemySprite->SetSize(glm::vec2(150, 153));
    enemySprite->SetZOrder(1);

    Actor* followEnemy = CreateActor<Actor>();
    SpriteRendererComponent* followEnemySpriteRenderer = followEnemy->AddComponent<SpriteRendererComponent>("goblin", "default");
    followEnemySpriteRenderer->SetSize(glm::vec2(150, 153));
    followEnemySpriteRenderer->SetZOrder(2);
    followEnemy->AttachToActor(enemy);
    followEnemy->SetLocalPosition(glm::vec2(165, 0));

    Actor* followEnemy2 = CreateActor<Actor>();
    SpriteRendererComponent* followEnemySpriteRenderer2 = followEnemy2->AddComponent<SpriteRendererComponent>("goblin", "default");
    followEnemySpriteRenderer2->SetSize(glm::vec2(150, 153));
    followEnemySpriteRenderer2->SetZOrder(3);
    //followEnemy2->AttachToActor(enemy);
    //followEnemy2->SetLocalPosition(glm::vec2(-165, 0));
    followEnemy2->AttachToActor(followEnemy);
    followEnemy2->SetLocalPosition(glm::vec2(-320, 0));


    Actor* cameraObject = CreateActor<Actor>();
    CameraComponent* camera = cameraObject->AddComponent<CameraComponent>();
    SetActiveCamera(camera);

    Actor* background = CreateActor<Actor>();
    SpriteRendererComponent* backgroundSpriteRenderer = background->AddComponent<SpriteRendererComponent>("background", "default");
    background->SetWorldPosition(glm::vec2(320, 240));
    backgroundSpriteRenderer->SetSize(glm::vec2(640, 480));
}

void BattleScene::LoadAssets()
{
    ResourceManager::LoadPNGTexture("Assets/button.png", "button"); 
    ResourceManager::LoadPNGTexture("Assets/goblin.png", "goblin");
    ResourceManager::LoadPNGTexture("Assets/battleback1_0.png", "background");
}