#ifndef __FLEE_ABILITY_H_INCLUDED__
#define __FLEE_ABILITY_H_INCLUDED__

#include "BattleLevel/Abilities/Ability.h"

class BattleManager;

/**
 * Ability used to flee from the current battle.
 * It interacts directly with the battle manager to end the current battle.
 */
class FleeAbility : public Ability
{
public:
	FleeAbility();

	bool CanExecuteAbility() const override;

	/**
	 * Ends the current battle.
	 */
	bool Execute() override;
	void SetBattleManager(BattleManager* inBattleManager) { battleManager = inBattleManager; }

private:
	// Battle manager responsible for ending the current battle.
	BattleManager* battleManager;
};

#endif // __FLEE_ABILITY_H_INCLUDED__