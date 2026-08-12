#ifndef __PLAYER_ACTIONS_MENU_INCLUDED__
#define __PLAYER_ACTIONS_MENU_INCLUDED__

#include "UI/UserWidget.h"

class AbilityButton;
class PlayerCharacter;

class PlayerActionsMenu : public UserWidget
{
public:
	void Construct() override;

	void SetSize(glm::vec2 inSize);

	void Show(PlayerCharacter* currentCharacter);
	void Hide();

private:
	void UpdateSize();

private:
	glm::vec2 size;
	bool isConstructed = false;

	AbilityButton* attackButton;
	AbilityButton* skillButton;
	AbilityButton* fleeButton;
};

#endif // __PLAYER_ACTIONS_MENU_INCLUDED__