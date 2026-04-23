#include "Enemy.h"
#include "Components/SpriteRendererComponent.h"

Enemy::Enemy(const char* _spriteFile, float _enemySpeed)
    : spriteFile(_spriteFile), enemySpeed(_enemySpeed)
{
}

void Enemy::Init()
{
    spriteRenderer = AddComponent<SpriteRendererComponent>();
    sprite = spriteRenderer->CreateSprite(spriteFile);
    sprite->SetSize(glm::vec2(300, 306));
    sprite->SetLayer(1);
    SetPosition(glm::vec2(320, 240));
}

void Enemy::Update(float deltaTime)
{
    glm::vec2 currentPos = GetPosition();

    if (currentPos.x <= 250 || currentPos.x >= 370)
    {
        enemyMoveDirection *= -1.0f;
    }

    SetPosition(glm::vec2(currentPos.x + (enemyMoveDirection * enemySpeed * deltaTime), currentPos.y));
}