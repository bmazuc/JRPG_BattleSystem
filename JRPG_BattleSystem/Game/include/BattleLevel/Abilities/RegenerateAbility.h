#ifndef __REGENERATE_ABILITY_H_INCLUDED__
#define __REGENERATE_ABILITY_H_INCLUDED__

#include "AbilityWithTarget.h"

class RegenerateAbility : public AbilityWithActorTarget
{
public:
	RegenerateAbility(unsigned int _manaCost = 0, int _healthRegen = 20, int _manaRegen = 20);

	bool Execute() override;

private:
	int healthRegen;
	int manaRegen;
};

#endif // __REGENERATE_ABILITY_H_INCLUDED__