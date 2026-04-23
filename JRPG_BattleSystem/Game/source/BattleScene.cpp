#include "BattleScene.h"
#include "Components/SpriteRendererComponent.h"
#include "Enemy.h"
#include "Components/CameraComponent.h"

BattleScene::BattleScene()
{
    Enemy* enemy = new Enemy("Assets/goblin.png", 3.0f);
    AddGameObject(enemy);
    enemy->SetSpeed(50.0f);

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