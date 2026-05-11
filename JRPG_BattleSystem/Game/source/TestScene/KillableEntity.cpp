#include "TestScene/KillableEntity.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Scene/PlayerController.h"
#include "Scene/Scene.h"

KillableEntity::KillableEntity(std::string textureName, std::string shaderName)
{
    spriteRenderer = SpawnComponent<SpriteRendererComponent>("Sprite render", nullptr,
        glm::vec2(0, 0), 0, glm::vec2(1, 1),
        textureName, shaderName);
}

void KillableEntity::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    if (playerController)
    {
        clickHandle = playerController->OnClick.Bind(std::bind(&KillableEntity::OnClick, this));
    }
}

void KillableEntity::OnClick()
{
    if (playerController)
    {
        glm::vec2 mousePos = playerController->GetMousePosition();

        if (IsHovered(mousePos))
        {
            playerController->OnClick.Unbind(clickHandle);
            Destroy();
        }
    }
}

bool KillableEntity::IsHovered(glm::vec2 mousePos)
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