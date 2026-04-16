#include "BattleSystemGame.h"
#include "Components/SpriteRenderer.h"

void BattleSystemGame::Init()
{
    enemy = new GameObject();
    SpriteRenderer* enemySpriteRenderer = enemy->AddComponent<SpriteRenderer>();
    Sprite* enemySprite = enemySpriteRenderer->CreateSprite("Assets/goblin.png");
    enemySprite->SetPosition(glm::vec2(320, 240));
    enemySprite->SetSize(glm::vec2(300, 306));
    enemySprite->SetLayer(1);

    scene->AddGameObject(enemy);


    GameObject* background = new GameObject();
    SpriteRenderer* backgroundSpriteRenderer = background->AddComponent<SpriteRenderer>();
    Sprite* backgroundSprite = backgroundSpriteRenderer->CreateSprite("Assets/battleback1_0.png");
    backgroundSprite->SetPosition(glm::vec2(320, 240));
    backgroundSprite->SetSize(glm::vec2(640, 480)); 

    scene->AddGameObject(background);
}

void BattleSystemGame::Update()
{
    // Temp for update test. Move enemy left to right
    Sprite* enemySprite = enemy->GetComponent<SpriteRenderer>()->GetSprite();

    if (enemySprite)
    {
        glm::vec2 currentPos = enemySprite->GetPosition();

        if (currentPos.x <= 250 || currentPos.x >= 370)
        {
            enemyMoveDirection *= -1.0f;
        }

        enemySprite->SetPosition(glm::vec2(currentPos.x + (enemyMoveDirection*enemySpeed), currentPos.y));
    }
}