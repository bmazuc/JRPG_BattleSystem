#include "BattleLevel/Abilities/AbilityWithTarget.h"

bool AbilityWithActorTarget::CanExecuteAbility()
{
	return target != nullptr;
}
