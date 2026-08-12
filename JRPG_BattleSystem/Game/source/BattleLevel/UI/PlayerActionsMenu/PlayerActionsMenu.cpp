#include "BattleLevel/UI/PlayerActionsMenu/PlayerActionsMenu.h"
#include "BattleLevel/UI/AbilityButton.h"
#include "Rendering/Material.h"
#include "BattleLevel/Characters/PlayerCharacter.h"
#include "UI/Text.h"

void PlayerActionsMenu::Construct()
{
	attackButton = CreateWidget<AbilityButton>("AttackButton", UISpawnInfo());
	attackButton->GetMaterial()->SetTexture("button");
	skillButton = CreateWidget<AbilityButton>("SkillButton1", UISpawnInfo());
	skillButton->GetMaterial()->SetTexture("button");
	fleeButton = CreateWidget<AbilityButton>("FleeButton", UISpawnInfo());
	fleeButton->GetMaterial()->SetTexture("button");

	Text* mainMenuButtonText = CreateWidget<Text>("FleeButtonText", UISpawnInfo(fleeButton, TransformSpace::Local));
	mainMenuButtonText->SetContent("Flee");
	mainMenuButtonText->SetSize(24);

	UpdateSize();

	isConstructed = true;
}

void PlayerActionsMenu::Show(PlayerCharacter* currentCharacter)
{
	if (!currentCharacter)
	{
		return;
	}

	fleeButton->AssociateAbility(currentCharacter->TryGetAbility("flee"));

	SetVisible(true);
}

void PlayerActionsMenu::Hide()
{
	SetVisible(false);

	fleeButton->AssociateAbility(nullptr);
}

void PlayerActionsMenu::SetSize(glm::vec2 inSize)
{ 
	size = inSize; 
	if (isConstructed)
	{
		UpdateSize();
	}
}

void PlayerActionsMenu::UpdateSize()
{
	glm::vec2 buttonSize = size;
	buttonSize.y /= 3.0f;

	attackButton->SetLocalPosition(glm::vec2(buttonSize.x / 2.0f, -buttonSize.y));
	attackButton->SetSize(buttonSize);

	skillButton->SetLocalPosition(glm::vec2(buttonSize.x / 2.0f, 0.0f));
	skillButton->SetSize(buttonSize);

	fleeButton->SetLocalPosition(glm::vec2(buttonSize.x / 2.0f, buttonSize.y));
	fleeButton->SetSize(buttonSize);
}