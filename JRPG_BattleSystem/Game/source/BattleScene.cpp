#include "BattleScene.h"
#include "Components/SpriteRendererComponent.h"
#include "Enemy.h"
#include "Components/CameraComponent.h"
#include "AutoDestroyImage.h"

BattleScene::BattleScene()
{
    AutoDestroyImage* image = CreateUIElement<AutoDestroyImage>();
    image->LoadPNG("Assets/button.png");
    image->SetWorldPosition(glm::vec2(100, 100));
    image->SetSize(glm::vec2(50, 50));

    Image* image2 = CreateUIElement<Image>();
    image2->LoadPNG("Assets/button.png");
    image2->SetWorldPosition(glm::vec2(100, 100));
    image2->SetSize(glm::vec2(25, 25));
    image2->SetParent(image);

    Enemy* enemy = CreateActors<Enemy>("Assets/goblin.png");
    enemy->SetWorldPosition(glm::vec2(320, 240));
    enemy->SetSpeed(50.0f);
    Sprite* enemySprite = enemy->GetSprite();
    enemySprite->SetSize(glm::vec2(300, 306));
    enemySprite->SetLayer(1);

    Actor* followEnemy = CreateActors<Actor>();
    SpriteRendererComponent* followEnemySpriteRenderer = followEnemy->AddComponent<SpriteRendererComponent>();
    Sprite* followEnemySprite = followEnemySpriteRenderer->CreateSprite("Assets/goblin.png");
    followEnemySprite->SetSize(glm::vec2(160, 120));
    followEnemySprite->SetLayer(2);
    followEnemy->SetWorldPosition(glm::vec2(320, 240));
    followEnemy->AttachToActor(enemy);

    Actor* followEnemy2 = CreateActors<Actor>();
    SpriteRendererComponent* followEnemySpriteRenderer2 = followEnemy2->AddComponent<SpriteRendererComponent>();
    Sprite* followEnemySprite2 = followEnemySpriteRenderer2->CreateSprite("Assets/goblin.png");
    followEnemySprite2->SetSize(glm::vec2(80, 60));
    followEnemySprite2->SetLayer(3);
    followEnemy2->SetWorldPosition(glm::vec2(320, 240));
    followEnemy2->AttachToActor(followEnemy);

    Actor* cameraObject = CreateActors<Actor>();
    CameraComponent* camera = cameraObject->AddComponent<CameraComponent>();
    SetActiveCamera(camera);

    Actor* background = CreateActors<Actor>();
    SpriteRendererComponent* backgroundSpriteRenderer = background->AddComponent<SpriteRendererComponent>();
    Sprite* backgroundSprite = backgroundSpriteRenderer->CreateSprite("Assets/battleback1_0.png");
    background->SetWorldPosition(glm::vec2(320, 240));
    backgroundSprite->SetSize(glm::vec2(640, 480));
}