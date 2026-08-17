#include "BattleLevel/Abilities/RegenerateAbility.h"
#include "BattleLevel/Characters/Character.h"

RegenerateAbility::RegenerateAbility(unsigned int _manaCost, int _healthRegen, int _manaRegen)
{
	name = "Regenerate";

	targetType = TargetType::ALLY;

	manaCost = _manaCost;

	healthRegen = _healthRegen;
	manaRegen = _manaRegen;
}

bool RegenerateAbility::Execute()
{
	if (!CanExecuteAbility())
	{
		return false;
	}

	PayCost();

	Character* characterTarget = dynamic_cast<Character*>(target);

	if (!characterTarget)
	{
		return false;
	}

	characterTarget->Regenerate(healthRegen, manaRegen);

	return true;
}