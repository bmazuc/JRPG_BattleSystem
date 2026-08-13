#ifndef __FLEE_ABILITY_H_INCLUDED__
#define __FLEE_ABILITY_H_INCLUDED__

#include "BattleLevel/Abilities/Ability.h"

class BattleManager;

class FleeAbility : public Ability
{
public:
	FleeAbility();

	bool CanExecuteAbility() override;

	bool Execute() override;
	void SetBattleManager(BattleManager* inBattleManager) { battleManager = inBattleManager; }

private:
	BattleManager* battleManager;
};

#endif // __FLEE_ABILITY_H_INCLUDED__