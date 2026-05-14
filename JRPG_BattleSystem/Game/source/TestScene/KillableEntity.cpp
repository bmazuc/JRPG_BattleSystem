#include "TestScene/KillableEntity.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Scene/PlayerController.h"
#include "Scene/Scene.h"

KillableEntity::KillableEntity(std::string textureName, std::string shaderName)
{
    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(), textureName, shaderName);
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

        if (spriteRenderer && spriteRenderer->IsHovered(mousePos))
        {
            playerController->OnClick.Unbind(clickHandle);
            MarkForDestruction();
        }
    }
}