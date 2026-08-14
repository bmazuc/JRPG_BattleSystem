#include "BattleLevel/Abilities/AbilityWithTarget.h"

bool AbilityWithActorTarget::CanExecuteAbility() const 
{
	return Ability::CanExecuteAbility() && (target != nullptr);
}
