#ifndef __CHARACTER_INFOS_TEXT_INCLUDED__
#define __CHARACTER_INFOS_TEXT_INCLUDED__

#include "UI/Text.h"
#include "Core/Delegate/Delegate.h"

class Character;

class CharacterInfosText : public Text
{
public:
	void AssociateCharacter(Character* character);

private:
	void UpdateHealth(int health, int maxHealth);
	void UpdateMana(int mana, int maxMana);
	void OnCharacterDeath(Character* character);

	void UpdateContent();

	DelegateHandle OnUpdateHealthHandle;
	DelegateHandle OnUpdateManaHandle;
	DelegateHandle OnCharacterDeathHandle;

	std::string characterName;
	std::string characterHealth;
	std::string characterMana;
};

#endif // __CHARACTER_INFOS_TEXT_INCLUDED__