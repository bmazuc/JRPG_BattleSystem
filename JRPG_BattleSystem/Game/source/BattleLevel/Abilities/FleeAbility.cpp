#include "BattleLevel/Abilities/FleeAbility.h"
#include "BattleLevel/BattleManager.h"

FleeAbility::FleeAbility()
{
	name = "Flee";
}

bool FleeAbility::CanExecuteAbility()
{
	return battleManager != nullptr;
}

bool FleeAbility::Execute()
{
	if (CanExecuteAbility())
	{
		battleManager->EndBattle();
		return true;
	}

	return false;
}
