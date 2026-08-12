#include "BattleLevel/UI/AbilityButton.h"
#include "BattleLevel/Ability/Ability.h"

void AbilityButton::OnClicked()
{
	if (ability)
	{
		ability->Execute();
	}
}