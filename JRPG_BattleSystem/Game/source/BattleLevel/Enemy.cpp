#include "BattleLevel/Enemy.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "World/PlayerController.h"

Enemy::Enemy(EnemyData data)
{
    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(),
        data.textureName, data.shaderName, data.color);

    spriteRenderer->SetSize(data.spriteSize);
    spriteRenderer->SetZOrder(1);
}

void Enemy::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    clickHandle = playerController->OnClick.Bind(std::bind(&Enemy::OnClick, this));
}

void Enemy::OnClick()
{
    if (playerController)
    {
        glm::vec2 mousePos = playerController->GetMousePosition();
        if (spriteRenderer && spriteRenderer->IsHovered(mousePos))
        {
            MarkForDestruction();
            OnDeath.Call();
        }
    }
}

void Enemy::BeginDestroy()
{
    Actor::BeginDestroy();
    if (playerController)
    {
        playerController->OnClick.Unbind(clickHandle);
    }
}