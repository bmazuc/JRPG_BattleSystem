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

        if (damageTimer <= 0.0f)
        {
            if (isPendingKill)
            {
                Kill();
            }
            OnBlinkEnd.Call();
        }
    }
}

void Character::TakeDamage(int damage)
{
    originalColor = spriteRenderer->GetMaterial()->GetColor();
    damageTimer = damageDuration;

    attributes.health -= damage;
    OnHealthUpdate.Call(attributes.health, attributes.maxHealth);

    if (attributes.health <= 0.0f)
    {
        isPendingKill = true;
    }

    OnDamageTaken.Call(this, damage);
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
        float lerp = t * 2.0f;
        spriteRenderer->GetMaterial()->SetColor(glm::mix(originalColor, glm::vec4(1.0f, 0.0f, 0.0f, originalColor.a), lerp));
    }
    else
    {
        float lerp = (t - 0.5f) * 2.0f;
        spriteRenderer->GetMaterial()->SetColor(glm::mix(glm::vec4(1.0f, 0.0f, 0.0f, originalColor.a), originalColor, lerp));
    }
}