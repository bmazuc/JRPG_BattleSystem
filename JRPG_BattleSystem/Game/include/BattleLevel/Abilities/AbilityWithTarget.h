#ifndef __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__
#define __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__

#include "Ability.h"

class Actor;

class AbilityWithActorTarget : public Ability
{
public:
	bool CanExecuteAbility() override;

	void SetTarget(Actor* inTarget) { target = inTarget; }

protected:
	Actor* target;
};

#endif // __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__