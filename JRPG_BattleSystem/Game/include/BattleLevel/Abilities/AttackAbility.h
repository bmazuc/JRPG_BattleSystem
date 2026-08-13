#ifndef __ATTACK_ABILITY_H_INCLUDED__
#define __ATTACK_ABILITY_H_INCLUDED__

#include "AbilityWithTarget.h"

class AttackAbility : public AbilityWithActorTarget
{
public:
	AttackAbility();

	bool Execute() override;
};

#endif // __ATTACK_ABILITY_H_INCLUDED__