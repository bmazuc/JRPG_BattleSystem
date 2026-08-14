#ifndef __PLAYER_ACTIONS_MENU_INCLUDED__
#define __PLAYER_ACTIONS_MENU_INCLUDED__

#include "UI/UserWidget.h"

class AbilityButton;
class PlayerCharacter;
class BattleManager;
class Text;

class PlayerActionsMenu : public UserWidget
{
public:
	void Construct() override;

	void SetSize(glm::vec2 inSize);
	void SetMargin(glm::vec2 inMargin) { margin = inMargin; }

	void Init(BattleManager* battleManager);
	void Show(PlayerCharacter* currentCharacter);
	void Hide();

private:
	void UpdateSize();

private:
	glm::vec2 size;
	glm::vec2 margin = glm::vec2(1.0f, 1.0f);

	bool isConstructed = false;

	AbilityButton* attackButton;
	AbilityButton* skillButton;
	AbilityButton* fleeButton;

	Text* attackButtonText;
	Text* skillButtonText;
	Text* fleeButtonText;
};

#endif // __PLAYER_ACTIONS_MENU_INCLUDED__