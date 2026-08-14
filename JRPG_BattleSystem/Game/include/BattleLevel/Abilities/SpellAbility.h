#ifndef __SPELL_H_INCLUDED__
#define __SPELL_H_INCLUDED__

#include "AbilityWithTarget.h"

class SpellAbility : public AbilityWithActorTarget
{
public:
	SpellAbility(unsigned int _manaCost = 0);

	bool Execute() override;
};

#endif // __SPELL_H_INCLUDED__