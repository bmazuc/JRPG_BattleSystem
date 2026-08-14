#include "BattleLevel/Abilities/Ability.h"
#include "BattleLevel/Characters/Character.h"

bool Ability::CanPayCost() const
{
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
		owner->UseMana(manaCost);
	}
}