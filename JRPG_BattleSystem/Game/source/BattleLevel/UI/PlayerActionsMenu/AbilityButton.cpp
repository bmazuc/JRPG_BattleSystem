#include "BattleLevel/UI/PlayerActionsMenu/AbilityButton.h"
#include "BattleLevel/Abilities/Ability.h"
#include "BattleLevel/BattleManager.h"

void AbilityButton::OnClicked()
{
	if (ability && battleManager && ability->CanPayCost())
	{
		battleManager->SetCurrentAbility(ability);
	}
}