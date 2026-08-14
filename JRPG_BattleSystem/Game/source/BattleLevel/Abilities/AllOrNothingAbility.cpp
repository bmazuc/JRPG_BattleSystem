#include "BattleLevel/Abilities/AllOrNothingAbility.h"
#include "BattleLevel/Characters/Character.h"

AllOrNothingAbility::AllOrNothingAbility(unsigned int _manaCost, int _bonusDamage)
{
	name = "All or Nothing";
	manaCost = _manaCost;
	bonusDamage = _bonusDamage;
}

bool AllOrNothingAbility::Execute()
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

	const CharacterAttributes& attributes = owner->GetAttributes();
	int damages = std::max(0, attributes.attack - defender->GetAttributes().defense) + (int)std::ceil(bonusDamage * (1.0f - (attributes.health / attributes.maxHealth)));
	defender->TakeDamage(damages);

	return true;
}