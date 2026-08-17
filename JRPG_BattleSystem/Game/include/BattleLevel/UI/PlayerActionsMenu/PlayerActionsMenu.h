#ifndef __PLAYER_ACTIONS_MENU_INCLUDED__
#define __PLAYER_ACTIONS_MENU_INCLUDED__

#include "UI/UserWidget.h"

class AbilityButton;
class PlayerCharacter;
class BattleManager;
class Text;

/**
 * UI menu used to display the actions available to the current player character.
 * The menu contains buttons for the character's attack, skill, and flee abilities.
 * Button availability is updated when the menu is shown based on the current character and their ability resource costs.
 */
class PlayerActionsMenu : public UserWidget
{
public:
	void Construct() override;

	void SetSize(glm::vec2 inSize);
	void SetMargin(glm::vec2 inMargin) { margin = inMargin; }
	void SetFontSize(float inFontSize) { fontSize = inFontSize; }

	/**
	 * Initializes the menu with the battle manager used to process actions.
	 */
	void Init(BattleManager* battleManager);
	/**
	 * Displays the menu for the specified player character.
	 * Updates button states and labels according to the character's available abilities and their resource costs.
	 */ 
	void Show(PlayerCharacter* currentCharacter);
	/**
	 * Hides the action menu and clears the currently associated action.
	 */
	void Hide();

private:
	/**
	 * Updates the size and position of all action buttons.
	 */
	void UpdateButtonsSize();

	glm::vec2 size;
	glm::vec2 margin = glm::vec2(1.0f, 1.0f);
	float fontSize = 20.0f;

	bool isConstructed = false;

	AbilityButton* attackButton;
	AbilityButton* skillButton;
	AbilityButton* fleeButton;

	Text* attackButtonText;
	Text* skillButtonText;
	Text* fleeButtonText;
};

#endif // __PLAYER_ACTIONS_MENU_INCLUDED__