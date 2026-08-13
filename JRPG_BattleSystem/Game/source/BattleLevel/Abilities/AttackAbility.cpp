#include "BattleLevel/Abilities/AttackAbility.h"
#include "BattleLevel/Characters/Character.h"

AttackAbility::AttackAbility()
{
	name = "Attack";
}

bool AttackAbility::Execute()
{
	if (!CanExecuteAbility())
	{
		return false;
	}

	Character* attacker = dynamic_cast<Character*>(owner);
	Character* defender = dynamic_cast<Character*>(target);

	if (!attacker || !defender)
	{
		return false;
	}

	int damages = std::max(0, attacker->GetAttributes().attack - defender->GetAttributes().defense);
	defender->TakeDamage(damages);

	return true;
}