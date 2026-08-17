#ifndef __CHARACTER_INFOS_TEXT_INCLUDED__
#define __CHARACTER_INFOS_TEXT_INCLUDED__

#include "UI/Text.h"
#include "Core/Delegate/Delegate.h"

class Character;

/**
 * Displays live health and mana information for a character.
 * Automatically updates its content when the associated character's health or mana changes, and unregisters its callbacks when the character dies.
 */
class CharacterInfosText : public Text
{
public:
	/**
	 * Associates the widget with a character.
	 * The widget subscribes to the character's health, mana, and death events.
	 */ 
	void AssociateCharacter(Character* character);

private:
	/**
	 * Updates the displayed health value.
	 */
	void UpdateHealth(int health, int maxHealth);
	/**
	 * Updates the displayed mana value.
	 */
	void UpdateMana(int mana, int maxMana);
	/**
	 * Handles the death of the associated character.
	 * Unregisters all character event callbacks.
	 */ 
	void OnCharacterDeath(Character* character);

	/**
	 * Rebuilds the displayed character information.
	 */
	void UpdateContent();

	DelegateHandle OnUpdateHealthHandle;
	DelegateHandle OnUpdateManaHandle;
	DelegateHandle OnCharacterDeathHandle;

	std::string characterName;
	//  Formatted health value displayed by the widget.
	std::string characterHealth;
	// Formatted mana value displayed by the widget.
	std::string characterMana;
};

#endif // __CHARACTER_INFOS_TEXT_INCLUDED__