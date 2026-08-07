#include "BattleLevel/Characters/Character.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"

Character::Character(CharacterData data)
{
    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(),
        data.textureName, data.shaderName, data.color);

    spriteRenderer->SetSize(data.spriteSize);
    spriteRenderer->SetZOrder(1);
}

void Character::Update(float deltaTime)
{
    if (damageTimer > 0.0f)
    {
        damageTimer -= deltaTime;

        float t = 1.0f - (damageTimer / damageDuration);
        Blink(t);

        if (damageTimer <= 0.0f && isPendingKill)
        {
            Kill();
        }
    }
}

void Character::TakeDamage(int damage)
{
    originalColor = spriteRenderer->GetMaterial()->GetColor();
    damageTimer = damageDuration;
    isPendingKill = true; // Currently directly set, later will only be if damage are deadly.
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

void Character::Blink(float t)
{
    if (t < 0.5f)
    {
        // Original -> rouge
        float lerp = t * 2.0f;
        spriteRenderer->GetMaterial()->SetColor(glm::mix(originalColor, glm::vec3(1.0f, 0.0f, 0.0f), lerp));
    }
    else
    {
        // Rouge -> original
        float lerp = (t - 0.5f) * 2.0f;
        spriteRenderer->GetMaterial()->SetColor(glm::mix(glm::vec3(1.0f, 0.0f, 0.0f), originalColor, lerp));
    }
}