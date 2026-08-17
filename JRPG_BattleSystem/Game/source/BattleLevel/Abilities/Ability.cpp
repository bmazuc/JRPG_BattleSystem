#include "BattleLevel/Abilities/Ability.h"
#include "BattleLevel/Characters/Character.h"

bool Ability::CanPayCost() const
{
	// Abilities with no mana cost are always affordable.
	if (manaCost == 0)
	{
		return true;
	}

	if (!owner || owner->GetAttributes().mana < (int)manaCost)
	{
		return false;
	}
	
	return true;
}

void Ability::PayCost()
{
	if (owner)
	{
		owner->ConsumeMana(manaCost);
	}
}