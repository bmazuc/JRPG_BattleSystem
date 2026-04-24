#include "BattleScene.h"
#include "Components/SpriteRendererComponent.h"
#include "Enemy.h"
#include "Components/CameraComponent.h"

BattleScene::BattleScene()
{
    Enemy* enemy = new Enemy("Assets/goblin.png");
    enemy->SetPosition(glm::vec2(320, 240));
    enemy->SetSpeed(50.0f);
    Sprite* enemySprite = enemy->GetSprite();
    enemySprite->SetSize(glm::vec2(300, 306));
    enemySprite->SetLayer(1);
    AddGameObject(enemy);

    Actor* followEnemy = new Actor();
    SpriteRendererComponent* followEnemySpriteRenderer = followEnemy->AddComponent<SpriteRendererComponent>();
    Sprite* followEnemySprite = followEnemySpriteRenderer->CreateSprite("Assets/goblin.png");
    followEnemySprite->SetSize(glm::vec2(160, 120));
    followEnemySprite->SetLayer(1);
    followEnemy->AttachToActor(enemy);
    followEnemy->SetPosition(glm::vec2(-220, -140));
    AddGameObject(followEnemy);

    Actor* cameraObject = new Actor();
    CameraComponent* camera = cameraObject->AddComponent<CameraComponent>();
    AddGameObject(cameraObject);
    SetActiveCamera(camera);

    Actor* background = new Actor();
    SpriteRendererComponent* backgroundSpriteRenderer = background->AddComponent<SpriteRendererComponent>();
    Sprite* backgroundSprite = backgroundSpriteRenderer->CreateSprite("Assets/battleback1_0.png");
    background->SetPosition(glm::vec2(320, 240));
    backgroundSprite->SetSize(glm::vec2(640, 480));

    AddGameObject(background);
}