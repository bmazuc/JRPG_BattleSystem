#include "BattleScene.h"
#include "Components/SpriteRendererComponent.h"
#include "Enemy.h"
#include "Components/CameraComponent.h"
#include "AutoDestroyImage.h"
#include "Core/ResourceManager.h"
#include "UI/Text.h"

void BattleScene::CreateScene()
{
    AutoDestroyImage* image = CreateUIElement<AutoDestroyImage>("button","default");
    image->SetWorldPosition(glm::vec2(100, 100));
    image->SetSize(glm::vec2(50, 50));

    Image* image2 = CreateUIElement<Image>("button", "default");
    image2->SetWorldPosition(glm::vec2(100, 100));
    image2->SetSize(glm::vec2(25, 25));
    image2->SetParent(image);

    Text* text = CreateUIElement<Text>("default");
    text->SetParent(image2);
    text->SetWorldPosition(glm::vec2(100, 100));
    text->SetContent("test");
    text->SetColor(glm::vec3(1, 0, 0));
    text->SetSize(24);

    Enemy* enemy = CreateActor<Enemy>("goblin", "default");
    enemy->SetWorldPosition(glm::vec2(320, 240));
    enemy->SetSpeed(50.0f);
    Sprite* enemySprite = enemy->GetSprite();
    enemySprite->SetSize(glm::vec2(300, 306));
    enemySprite->SetLayer(1);

    Actor* followEnemy = CreateActor<Actor>();
    SpriteRendererComponent* followEnemySpriteRenderer = followEnemy->AddComponent<SpriteRendererComponent>("goblin", "default");
    Sprite* followEnemySprite = followEnemySpriteRenderer->GetSprite();
    followEnemySprite->SetSize(glm::vec2(160, 120));
    followEnemySprite->SetLayer(2);
    followEnemy->SetWorldPosition(glm::vec2(320, 240));
    followEnemy->AttachToActor(enemy);

    Actor* followEnemy2 = CreateActor<Actor>();
    SpriteRendererComponent* followEnemySpriteRenderer2 = followEnemy2->AddComponent<SpriteRendererComponent>("goblin", "default");
    Sprite* followEnemySprite2 = followEnemySpriteRenderer2->GetSprite();
    followEnemySprite2->SetSize(glm::vec2(80, 60));
    followEnemySprite2->SetLayer(3);
    followEnemy2->SetWorldPosition(glm::vec2(320, 240));
    followEnemy2->AttachToActor(followEnemy);

    Actor* cameraObject = CreateActor<Actor>();
    CameraComponent* camera = cameraObject->AddComponent<CameraComponent>();
    SetActiveCamera(camera);

    Actor* background = CreateActor<Actor>();
    SpriteRendererComponent* backgroundSpriteRenderer = background->AddComponent<SpriteRendererComponent>("background", "default");
    background->SetWorldPosition(glm::vec2(320, 240));
    backgroundSpriteRenderer->GetSprite()->SetSize(glm::vec2(640, 480));
}

void BattleScene::LoadAssets()
{
    ResourceManager::LoadPNGTexture("Assets/button.png", "button"); 
    ResourceManager::LoadPNGTexture("Assets/goblin.png", "goblin");
    ResourceManager::LoadPNGTexture("Assets/battleback1_0.png", "background");
}