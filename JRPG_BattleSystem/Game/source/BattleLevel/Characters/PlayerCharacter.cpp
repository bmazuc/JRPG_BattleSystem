#include "BattleLevel/Characters/PlayerCharacter.h"
#include "BattleLevel/Abilities/FleeAbility.h"
#include "BattleLevel/Abilities/AttackAbility.h"

PlayerCharacter::PlayerCharacter(CharacterData data)
	: Character(data)
{
    AttackAbility* attackAbility = new AttackAbility();
    attackAbility->SetOwner(this);
    abilities["attack"] = attackAbility;

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
