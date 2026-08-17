#ifndef __ATTACK_ABILITY_H_INCLUDED__
#define __ATTACK_ABILITY_H_INCLUDED__

#include "AbilityWithTarget.h"
/**
 * Basic attack.
 */
class AttackAbility : public AbilityWithActorTarget
{
public:
	AttackAbility();

	/**
	 * Executes the attack against the selected target.
	 * Deals damage based on the owner's attack value and the target's defense value.
	 */
	bool Execute() override;
};

#endif // __ATTACK_ABILITY_H_INCLUDED__