#include "BattleScene/Enemy.h"
#include "Components/Rendering/SpriteRendererComponent.h"

Enemy::Enemy(EnemyData data)
{
    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(),
        data.textureName, data.shaderName, data.color);

    spriteRenderer->SetSize(data.spriteSize);
    spriteRenderer->SetZOrder(1);
}