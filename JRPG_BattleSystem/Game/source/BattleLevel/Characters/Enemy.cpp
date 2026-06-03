#include "BattleLevel/Enemy.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "World/PlayerController.h"

Enemy::Enemy(CharacterData data)
    : Character(data)
{
}

void Enemy::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    clickHandle = playerController->OnClick.Bind(this, &Enemy::OnClick);
}

void Enemy::OnClick()
{
    if (playerController)
    {
        glm::vec2 mousePos = playerController->GetMousePosition();
        if (spriteRenderer && spriteRenderer->IsHovered(mousePos))
        {
            OnSelected.Call(this);
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