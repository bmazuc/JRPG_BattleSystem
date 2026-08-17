#include "BattleLevel/Characters/Character.h"
#include "Components/Rendering/SpriteRendererComponent.h"
#include "Rendering/Material.h"
#include "World/PlayerController.h"

Character::Character(CharacterData data)
{
    characterName = data.characterName;

    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(),
        data.textureName, data.shaderName, data.color);

    spriteRenderer->SetSize(data.spriteSize);
    spriteRenderer->SetZOrder(1);

    attributes = data.attributes;
}

void Character::SetupInputs(PlayerController* _playerController)
{
    playerController = _playerController;
    clickHandle = playerController->OnClick.Bind(this, &Character::OnClick);
}

void Character::OnClick()
{
    if (playerController)
    {
        glm::vec2 mousePos = playerController->GetMousePosition();
        if (spriteRenderer && spriteRenderer->IsHovered(mousePos))
        {
            OnSelected.Call(this);
        }
    }
}

void Character::Update(float deltaTime)
{
    if (blinkTimer > 0.0f)
    {
        blinkTimer -= deltaTime;

        // Convert remaining time into a normalized interpolation value.
        float t = 1.0f - (blinkTimer / blinkDuration);
        Blink(t);

        if (blinkTimer <= 0.0f)
        {
            // Delay destruction until the visual feedback has finished.
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
    blinkColor = Colors::Red;
    blinkColor.a = originalColor.a;

    blinkTimer = blinkDuration;

    attributes.health -= damage;
    OnHealthUpdate.Call(attributes.health, attributes.maxHealth);

    if (attributes.health <= 0.0f)
    {
        isPendingKill = true;
    }

    OnDamageTaken.Call(this, damage);
}

void Character::ConsumeMana(int manaAmount)
{
    attributes.mana -= manaAmount;

    if (attributes.mana < 0)
    {
        attributes.mana = 0;
    }
    
    OnManaUpdate.Call(attributes.mana, attributes.maxMana);
}

void Character::Regenerate(int healthRegen, int manaRegen)
{
    originalColor = spriteRenderer->GetMaterial()->GetColor();
    blinkColor = Colors::Green;
    blinkColor.a = originalColor.a;

    blinkTimer = blinkDuration;

    attributes.health += healthRegen;
    if (attributes.health > attributes.maxHealth)
    {
        attributes.health = attributes.maxHealth;
    }

    attributes.mana += manaRegen;
    if (attributes.mana > attributes.maxMana)
    {
        attributes.mana = attributes.maxMana;
    }

    OnHealthUpdate.Call(attributes.health, attributes.maxHealth);
    OnManaUpdate.Call(attributes.mana, attributes.maxMana);

    // Reuse the damage display system to display the healing amount.
    OnDamageTaken.Call(this, healthRegen);
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
        spriteRenderer->GetMaterial()->SetColor(glm::mix(originalColor, blinkColor, lerp));
    }
    else
    {
        float lerp = (t - 0.5f) * 2.0f;
        spriteRenderer->GetMaterial()->SetColor(glm::mix(blinkColor, originalColor, lerp));
    }
}

void Character::BeginDestroy()
{
    Actor::BeginDestroy();


    if (playerController)
    {
        playerController->OnClick.Unbind(clickHandle);
    }
}
