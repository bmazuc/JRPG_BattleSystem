#include "BattleLevel/Characters/Character.h"
#include "Components/Rendering/SpriteRendererComponent.h"

Character::Character(CharacterData data)
{
    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(),
        data.textureName, data.shaderName, data.color);

    spriteRenderer->SetSize(data.spriteSize);
    spriteRenderer->SetZOrder(1);
}

void Character::Kill()
{
    if (isAlive)
    {
        MarkForDestruction();
        isAlive = false;
        OnDeath.Call(this);
    }
}