#include "BattleScene/Enemy.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Scene/PlayerController.h"
#include "Scene/Scene.h"

Enemy::Enemy(std::string textureName, std::string shaderName)
{
    spriteRenderer = AddComponent<SpriteRendererComponent>("Sprite render", nullptr,
        glm::vec2(0, 0), 0, glm::vec2(1, 1),
        textureName, shaderName);
}

void Enemy::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    if (playerController)
    {
        playerController->OnClick.Bind(std::bind(&Enemy::OnClick, this));
    }
}

void Enemy::OnClick()
{
    if (playerController)
    { 
        glm::vec2 mousePos = playerController->GetMousePosition();

        if (IsHovered(mousePos))
        {
            isMoving = !isMoving;
        }
    }
}

bool Enemy::IsHovered(glm::vec2 mousePos)
{
    if (!spriteRenderer)
    {
        return false;
    }

    glm::vec2 mouseWorldPos = scene->ScreenToWorld(mousePos);

    glm::vec2 bounds = (spriteRenderer->GetSize() * GetWorldScale()) / 2.0f;
    glm::vec2 worldPos = spriteRenderer->GetWorldPosition();

    return mouseWorldPos.x >= worldPos.x - bounds.x &&
        mouseWorldPos.x <= worldPos.x + bounds.x &&
        mouseWorldPos.y >= worldPos.y - bounds.y &&
        mouseWorldPos.y <= worldPos.y + bounds.y;
}

void Enemy::Update(float deltaTime)
{
    if (!isMoving)
    {
        return;
    }

    glm::vec2 currentPos = GetWorldPosition();

    if (currentPos.x <= 250 || currentPos.x >= 370)
    {
        enemyMoveDirection *= -1.0f;
    }

    SetLocalPosition(glm::vec2(currentPos.x + (enemyMoveDirection * enemySpeed * deltaTime), currentPos.y));
}