#include "Enemy.h"
#include "Components/SpriteRendererComponent.h"

Enemy::Enemy(const char* spriteFile)
{
    spriteRenderer = AddComponent<SpriteRendererComponent>();
    sprite = spriteRenderer->CreateSprite(spriteFile);
}

void Enemy::Update(float deltaTime)
{
    timer += deltaTime;

    glm::vec2 currentPos = GetWorldPosition();

    if (currentPos.x <= 250 || currentPos.x >= 370)
    {
        enemyMoveDirection *= -1.0f;
    }

    SetLocalPosition(glm::vec2(currentPos.x + (enemyMoveDirection * enemySpeed * deltaTime), currentPos.y));

    if (timer >= 6)
    {
        // Destroy should not be called twice but I do it to check if it crashes.
        Destroy();
        Destroy();
    }
}