#include "TestScene/MovingEntity.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Scene/PlayerController.h"
#include "Scene/Scene.h"

MovingEntity::MovingEntity(std::string textureName, std::string shaderName)
{
    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(), textureName, shaderName);
}

void MovingEntity::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    if (playerController)
    {
        playerController->OnClick.Bind(std::bind(&MovingEntity::OnClick, this));
    }
}

void MovingEntity::OnClick()
{
    if (playerController)
    { 
        glm::vec2 mousePos = playerController->GetMousePosition();

        if (spriteRenderer && spriteRenderer->IsHovered(mousePos))
        {
            isMoving = !isMoving;
        }
    }
}

void MovingEntity::Update(float deltaTime)
{
    if (!isMoving)
    {
        return;
    }

    glm::vec2 currentPos = GetWorldPosition();

    if (currentPos.x <= 250 || currentPos.x >= 370)
    {
        moveDirection *= -1.0f;
    }

    SetLocalPosition(glm::vec2(currentPos.x + (moveDirection * speed * deltaTime), currentPos.y));
}