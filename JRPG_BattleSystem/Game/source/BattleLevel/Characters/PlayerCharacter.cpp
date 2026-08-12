#include "BattleLevel/Characters/PlayerCharacter.h"
#include "BattleLevel/UI/FleeAbility.h"

PlayerCharacter::PlayerCharacter(CharacterData data)
	: Character(data)
{
    abilities["flee"] = new FleeAbility();
}

void PlayerCharacter::BeginDestroy()
{
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
