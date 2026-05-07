#include "BattleScene/Enemy.h"
#include "Components/Rendering/SpriteRendererComponent.h"

Enemy::Enemy(EnemyData data)
{
    spriteRenderer = AddComponent<SpriteRendererComponent>("Sprite render", nullptr, 
        glm::vec2(0, 0), 0, glm::vec2(1, 1),
        data.textureName, data.shaderName, data.color);

    spriteRenderer->SetSize(data.spriteSize);
    spriteRenderer->SetZOrder(1);
}