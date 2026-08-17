#ifndef __ALL_OR_NOTHING_ABILITY_H_INCLUDED__
#define __ALL_OR_NOTHING_ABILITY_H_INCLUDED__

#include "AbilityWithTarget.h"

/**
 * Attack that gains bonus damage as the owner's health decreases.
 * Skill used by warrior.
 */
class AllOrNothingAbility : public AbilityWithActorTarget
{
public:
	AllOrNothingAbility(unsigned int _manaCost = 0, int _bonusDamage = 15);

	/**
	 * Executes the attack against the selected target.
	 */
	bool Execute() override;

private:
	// Maximum bonus damage granted by the ability.
	int bonusDamage;
};

#endif // __ALL_OR_NOTHING_ABILITY_H_INCLUDED__