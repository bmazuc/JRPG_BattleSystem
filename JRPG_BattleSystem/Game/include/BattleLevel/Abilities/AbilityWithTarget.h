#ifndef __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__
#define __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__

#include "Ability.h"

/**
 * Defines the type of character that can be targeted by an ability.
 */
enum class TargetType
{
	ENEMY,
	ALLY
};

class Actor;

/**
 * Base class for abilities targeting a character.
 * Extends Ability with target management and validation.
 * The target type determines whether the ability is intended for an enemy or an ally.
 */
class AbilityWithActorTarget : public Ability
{
public:
	/**
	 * Checks whether the ability has a valid target and its mana cost can be paid.
	 */ 
	bool CanExecuteAbility() const override;

	/**
	 * Sets the character targeted by the ability.
	 */
	void SetTarget(Actor* inTarget) { target = inTarget; }

	TargetType GetTargetType() { return targetType; }

protected:
	// Character targeted by the ability.
	Actor* target;
	// Type of character expected as the target.
	TargetType targetType = TargetType::ENEMY;
};

#endif // __ABILITY_WITH_ACTOR_TARGET_H_INCLUDED__