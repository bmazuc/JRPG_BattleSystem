#include "BattleSystemGame.h"
#include "Components/SpriteRenderer.h"
#include "Enemy.h"

void BattleSystemGame::Init()
{
    Enemy* enemy = new Enemy("Assets/goblin.png", 3.0f);
    scene->AddGameObject(enemy);

    GameObject* background = new GameObject();
    SpriteRenderer* backgroundSpriteRenderer = background->AddComponent<SpriteRenderer>();
    Sprite* backgroundSprite = backgroundSpriteRenderer->CreateSprite("Assets/battleback1_0.png");
    backgroundSprite->SetPosition(glm::vec2(320, 240));
    backgroundSprite->SetSize(glm::vec2(640, 480)); 

    scene->AddGameObject(background);

    Game::Init();
}