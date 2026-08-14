#ifndef __ALL_OR_NOTHING_ABILITY_H_INCLUDED__
#define __ALL_OR_NOTHING_ABILITY_H_INCLUDED__

#include "AbilityWithTarget.h"

class AllOrNothingAbility : public AbilityWithActorTarget
{
public:
	AllOrNothingAbility(unsigned int _manaCost = 0, int _bonusDamage = 15);

	bool Execute() override;

private:
	int bonusDamage;
};

#endif // __ALL_OR_NOTHING_ABILITY_H_INCLUDED__