#include "BattleSystemGame.h"
#include "SpriteRenderer.h"

void BattleSystemGame::Init()
{
    GameObject* background = new GameObject();
    SpriteRenderer* backgroundSpriteRenderer = background->AddComponent<SpriteRenderer>();
    Sprite* backgroundSprite = backgroundSpriteRenderer->CreateSprite("Assets/battleback1_0.png");
    backgroundSprite->SetPosition(glm::vec2(320, 240));
    backgroundSprite->SetSize(glm::vec2(640, 480));

    scene->AddGameObject(background);

    GameObject* enemy = new GameObject();
    SpriteRenderer* enemySpriteRenderer = enemy->AddComponent<SpriteRenderer>();
    Sprite* enemySprite = enemySpriteRenderer->CreateSprite("Assets/goblin.png");
    enemySprite->SetPosition(glm::vec2(320, 240));
    enemySprite->SetSize(glm::vec2(300, 306));

    scene->AddGameObject(enemy);
}

void BattleSystemGame::Update()
{

}