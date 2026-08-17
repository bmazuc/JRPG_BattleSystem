#ifndef __ABILITY_BUTTON_H_INCLUDED__
#define __ABILITY_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class Ability;
class BattleManager;

/**
 * Button associated with a gameplay ability.
 * When clicked, the button validates the associated ability and asks the battle manager to make it the currently selected action.
 */
class AbilityButton : public Button
{
public:
	void OnClicked() override;

	void SetBattleManager(BattleManager* inBattleManager) { battleManager = inBattleManager; }
	void AssociateAbility(Ability* inAbility) { ability = inAbility; }

private:
	BattleManager* battleManager;
	Ability* ability;
};

#endif // __ABILITY_BUTTON_H_INCLUDED__