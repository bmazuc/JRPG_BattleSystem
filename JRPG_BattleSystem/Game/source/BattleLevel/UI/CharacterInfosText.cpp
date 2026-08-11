#include "BattleLevel/UI/CharacterInfosText.h"
#include "BattleLevel/Characters/Character.h"

void CharacterInfosText::AssociateCharacter(Character* character)
{
	if (character)
	{
		OnUpdateHealthHandle = character->OnHealthUpdate.Bind(this, &CharacterInfosText::UpdateHealth);
		OnUpdateManaHandle = character->OnManaUpdate.Bind(this, &CharacterInfosText::UpdateMana);
		OnCharacterDeathHandle = character->OnDeath.Bind(this, &CharacterInfosText::OnCharacterDeath);

		characterName = character->GetCharacterName();
		const CharacterAttributes characterAttributes = character->GetAttributes();
		characterHealth = "HP : " + std::to_string(characterAttributes.health) + " / " + std::to_string(characterAttributes.maxHealth);
		characterMana = "MP : " + std::to_string(characterAttributes.health) + " / " + std::to_string(characterAttributes.maxHealth);
		UpdateContent();
	}
}

void CharacterInfosText::OnCharacterDeath(Character* character)
{
	character->OnHealthUpdate.Unbind(OnUpdateHealthHandle);
	character->OnManaUpdate.Unbind(OnUpdateManaHandle);
	character->OnDeath.Unbind(OnCharacterDeathHandle);
}

void CharacterInfosText::UpdateHealth(int health, int maxHealth)
{
	characterHealth = "HP : " + std::to_string(health) + " / " + std::to_string(maxHealth);
	UpdateContent();
}

void CharacterInfosText::UpdateMana(int mana, int maxMana)
{
	characterMana = "MP : " + std::to_string(mana) + " / " + std::to_string(maxMana);
	UpdateContent();
}

void CharacterInfosText::UpdateContent()
{
	SetContent(characterName + "   " + characterHealth + "   " + characterMana);
}