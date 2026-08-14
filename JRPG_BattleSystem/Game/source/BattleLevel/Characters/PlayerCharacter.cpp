#include "BattleLevel/Characters/PlayerCharacter.h"
#include "BattleLevel/Abilities/FleeAbility.h"
#include "BattleLevel/Abilities/AttackAbility.h"
#include "Components/Rendering/SpriteRendererComponent.h"

PlayerCharacter::PlayerCharacter(PlayerCharacterData data)
{
    characterName = data.characterName;

    spriteRenderer = SpawnSceneComponent<SpriteRendererComponent>("Sprite render", SceneComponentSpawnInfo(),
        data.textureName, data.shaderName, data.color);

    spriteRenderer->SetSize(data.spriteSize);
    spriteRenderer->SetZOrder(1);

    attributes = data.attributes;

    AttackAbility* attackAbility = new AttackAbility();
    attackAbility->SetOwner(this);
    abilities["attack"] = attackAbility;

    data.skill->SetOwner(this);
    abilities["skill"] = data.skill;

    FleeAbility* fleeAbility = new FleeAbility();
    fleeAbility->SetOwner(this);
    abilities["flee"] = fleeAbility;
}

void PlayerCharacter::BeginDestroy()
{
    Actor::BeginDestroy();

    for (auto& it : abilities)
    {
        delete it.second;
        it.second = nullptr;
    }
}

Ability* PlayerCharacter::TryGetAbility(std::string abilityName)
{
    auto it = abilities.find(abilityName);
    if (it != abilities.end())
    {
        return it->second;
    }

    return nullptr;
}

const Ability* PlayerCharacter::TryGetAbility(std::string abilityName) const
{
    auto it = abilities.find(abilityName);
    if (it != abilities.end())
    {
        return it->second;
    }

    return nullptr;
}
