#include "BattleLevel/Abilities/SpellAbility.h"
#include "BattleLevel/Characters/Character.h"

SpellAbility::SpellAbility(unsigned int _manaCost)
{
	name = "Spell";

	manaCost = _manaCost;
}

bool SpellAbility::Execute()
{
	if (!CanExecuteAbility())
	{
		return false;
	}

	PayCost();

	Character* defender = dynamic_cast<Character*>(target);

	if (!owner || !defender)
	{
		return false;
	}

	int damages = std::max(0, owner->GetAttributes().magickAttack - defender->GetAttributes().magickDefense);
	defender->TakeDamage(damages);

	return true;
}