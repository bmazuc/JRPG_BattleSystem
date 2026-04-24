#include "Enemy.h"
#include "Components/SpriteRendererComponent.h"

Enemy::Enemy(const char* spriteFile)
{
    spriteRenderer = AddComponent<SpriteRendererComponent>();
    sprite = spriteRenderer->CreateSprite(spriteFile);
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