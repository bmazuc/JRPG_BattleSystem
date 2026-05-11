#include "TestScene/RotatingEntity.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Scene/PlayerController.h"
#include "Scene/Scene.h"

RotatingEntity::RotatingEntity(std::string textureName, std::string shaderName)
{
    spriteRenderer = SpawnComponent<SpriteRendererComponent>("Sprite render", nullptr,
        glm::vec2(0, 0), 0, glm::vec2(1, 1),
        textureName, shaderName);
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

        if (IsHovered(mousePos))
        {
            isRotating = !isRotating;
        }
    }
}

bool RotatingEntity::IsHovered(glm::vec2 mousePos)
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

void RotatingEntity::Update(float deltaTime)
{
    if (!isRotating)
    {
        return;
    }

    glm::vec2 currentPos = GetWorldPosition();

    SetLocalRotate(GetLocalRotate() + speed * deltaTime);
}