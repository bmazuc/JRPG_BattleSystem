#include "BattleScene/RotatingEnemy.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Scene/PlayerController.h"
#include "Scene/Scene.h"

RotatingEnemy::RotatingEnemy(std::string textureName, std::string shaderName)
{
    spriteRenderer = AddComponent<SpriteRendererComponent>(textureName, shaderName);
}

void RotatingEnemy::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    if (playerController)
    {
        playerController->OnClick.Bind(std::bind(&RotatingEnemy::OnClick, this));
    }
}

void RotatingEnemy::OnClick()
{
    if (playerController)
    {
        glm::vec2 mousePos = playerController->GetMousePosition();

        if (IsHovered(mousePos))
        {
            isRotating = !isRotating;
        }
    }
}

bool RotatingEnemy::IsHovered(glm::vec2 mousePos)
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

void RotatingEnemy::Update(float deltaTime)
{
    if (!isRotating)
    {
        return;
    }

    glm::vec2 currentPos = GetWorldPosition();

    SetLocalRotate(GetLocalRotate() + enemySpeed * deltaTime);
}