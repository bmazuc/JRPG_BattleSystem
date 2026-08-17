#ifndef __SPELL_H_INCLUDED__
#define __SPELL_H_INCLUDED__

#include "AbilityWithTarget.h"

/**
 * Attack that uses the owner's magical attack value.
 * Skill used by wizard.
 */
class SpellAbility : public AbilityWithActorTarget
{
public:
	SpellAbility(unsigned int _manaCost = 0);

	/**
	 * Executes the attack against the selected target.
	 * Deals damage based on the owner's magical attack value and the target's magical defense value.
	 */
	bool Execute() override;
};

#endif // __SPELL_H_INCLUDED__