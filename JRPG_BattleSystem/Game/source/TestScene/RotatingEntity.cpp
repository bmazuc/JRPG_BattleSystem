#include "TestScene/RotatingEntity.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Scene/PlayerController.h"
#include "Scene/Scene.h"

RotatingEntity::RotatingEntity(std::string textureName, std::string shaderName)
{
    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(), textureName, shaderName);
}

void RotatingEntity::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    if (playerController)
    {
        playerController->OnClick.Bind(std::bind(&RotatingEntity::OnClick, this));
    }
}

void RotatingEntity::OnClick()
{
    if (playerController)
    {
        glm::vec2 mousePos = playerController->GetMousePosition();

        if (spriteRenderer && spriteRenderer->IsHovered(mousePos))
        {
            isRotating = !isRotating;
        }
    }
}

void RotatingEntity::Update(float deltaTime)
{
    if (!isRotating)
    {
        return;
    }

    glm::vec2 currentPos = GetWorldPosition();

    SetLocalRotate(GetLocalRotate() + speed * deltaTime);
}