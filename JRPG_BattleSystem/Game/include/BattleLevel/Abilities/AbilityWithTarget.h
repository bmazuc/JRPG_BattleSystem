#ifndef __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__
#define __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__

#include "Ability.h"

enum class TargetType
{
	ENEMY,
	ALLY
};

class Actor;

class AbilityWithActorTarget : public Ability
{
public:
	bool CanExecuteAbility() const override;

	void SetTarget(Actor* inTarget) { target = inTarget; }

	TargetType GetTargetType() { return targetType; }

protected:
	Actor* target;

	TargetType targetType = TargetType::ENEMY;
};

#endif // __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__