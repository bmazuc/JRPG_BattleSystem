#include "BattleLevel/UI/FleeAbility.h"
#include "BattleLevel/BattleManager.h"

FleeAbility::FleeAbility()
{
	name = "Flee";
}

void FleeAbility::Execute()
{
	if (battleManager)
	{
		battleManager->EndBattle();
	}
}
