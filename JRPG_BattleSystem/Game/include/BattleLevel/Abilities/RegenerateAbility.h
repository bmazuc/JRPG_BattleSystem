#ifndef __REGENERATE_ABILITY_H_INCLUDED__
#define __REGENERATE_ABILITY_H_INCLUDED__

#include "AbilityWithTarget.h"

/**
 * Healing and mana regeneration ability.
 * Skill used by cleric.
 */
class RegenerateAbility : public AbilityWithActorTarget
{
public:
	RegenerateAbility(unsigned int _manaCost = 0, int _healthRegen = 20, int _manaRegen = 20);

	/**
	 * Restores health and mana to the selected ally.
	 */
	bool Execute() override;

private:
	// Amount of health restored by the ability.
	int healthRegen;
	// Amount of mana restored by the ability.
	int manaRegen;
};

#endif // __REGENERATE_ABILITY_H_INCLUDED__