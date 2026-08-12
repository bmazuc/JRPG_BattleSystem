#ifndef __ABILITY_BUTTON_H_INCLUDED__
#define __ABILITY_BUTTON_H_INCLUDED__

#include "UI/Button.h"

class Ability;

class AbilityButton : public Button
{
public:
	void OnClicked() override;

	void AssociateAbility(Ability* inAbility) { ability = inAbility; }

private:
	Ability* ability;
};

#endif // __ABILITY_BUTTON_H_INCLUDED__