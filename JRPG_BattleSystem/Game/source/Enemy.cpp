#include "Enemy.h"
#include "Components/SpriteRenderer.h"

Enemy::Enemy(const char* _spriteFile, float _enemySpeed)
    : spriteFile(_spriteFile), enemySpeed(_enemySpeed)
{
}

void Enemy::Init()
{
    spriteRenderer = AddComponent<SpriteRenderer>();
    sprite = spriteRenderer->CreateSprite(spriteFile);
    sprite->SetPosition(glm::vec2(320, 240));
    sprite->SetSize(glm::vec2(300, 306));
    sprite->SetLayer(1);
}

void Enemy::Update()
{
    if (sprite)
    {
        glm::vec2 currentPos = sprite->GetPosition();

        if (currentPos.x <= 250 || currentPos.x >= 370)
        {
            enemyMoveDirection *= -1.0f;
        }

        sprite->SetPosition(glm::vec2(currentPos.x + (enemyMoveDirection * enemySpeed), currentPos.y));
    }
}