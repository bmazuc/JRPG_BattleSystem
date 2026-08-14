#include "BattleLevel/UI/PlayerActionsMenu/PlayerActionsMenu.h"
#include "BattleLevel/UI/PlayerActionsMenu/AbilityButton.h"
#include "Rendering/Material.h"
#include "BattleLevel/Characters/PlayerCharacter.h"
#include "UI/Text.h"
#include "BattleLevel/Abilities/Ability.h"

void PlayerActionsMenu::Construct()
{
	attackButton = CreateWidget<AbilityButton>("AttackButton", UISpawnInfo());
	attackButton->GetMaterial()->SetTexture("button");
	skillButton = CreateWidget<AbilityButton>("SkillButton1", UISpawnInfo());
	skillButton->GetMaterial()->SetTexture("button");
	fleeButton = CreateWidget<AbilityButton>("FleeButton", UISpawnInfo());
	fleeButton->GetMaterial()->SetTexture("button");

	attackButtonText = CreateWidget<Text>("AttackButtonText", UISpawnInfo(attackButton, TransformSpace::Local));
	attackButtonText->SetSize(20);

	skillButtonText = CreateWidget<Text>("SkillButtonText", UISpawnInfo(skillButton, TransformSpace::Local));
	skillButtonText->SetSize(20);

	fleeButtonText = CreateWidget<Text>("FleeButtonText", UISpawnInfo(fleeButton, TransformSpace::Local));
	fleeButtonText->SetSize(20);

	UpdateSize();

	isConstructed = true;
}

void PlayerActionsMenu::Init(BattleManager* battleManager)
{
	attackButton->SetBattleManager(battleManager);
	skillButton->SetBattleManager(battleManager);
	fleeButton->SetBattleManager(battleManager);
}

void PlayerActionsMenu::Show(PlayerCharacter* currentCharacter)
{
	if (!currentCharacter)
	{
		return;
	}
	Ability* ability = currentCharacter->TryGetAbility("attack");

	if (ability)
	{
		Color color = ability->CanPayCost() ? Colors::White : Colors::Grey;

		attackButton->AssociateAbility(ability->CanPayCost() ? ability : nullptr);
		attackButton->GetMaterial()->SetColor(color);
		attackButtonText->SetColor(color);
		attackButtonText->SetContent(ability->GetName());
	}

	if (ability = currentCharacter->TryGetAbility("skill"))
	{
		Color color = ability->CanPayCost() ? Colors::White : Colors::Grey;

		skillButton->AssociateAbility(ability->CanPayCost() ? ability : nullptr);
		skillButton->GetMaterial()->SetColor(color);
		skillButtonText->SetColor(color);
		skillButtonText->SetContent(ability->GetName() + " [" + std::to_string(ability->GetManaCost()) + "]");
	}

	if (ability = currentCharacter->TryGetAbility("flee"))
	{
		Color color = ability->CanPayCost() ? Colors::White : Colors::Grey;

		fleeButton->AssociateAbility(ability->CanPayCost() ? ability : nullptr);
		fleeButton->GetMaterial()->SetColor(color);
		fleeButtonText->SetColor(color);
		fleeButtonText->SetContent(ability->GetName());
	}

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
	attackButton->SetSize(buttonSize - (margin / 2.0f));

	skillButton->SetLocalPosition(glm::vec2(buttonSize.x / 2.0f, 0.0f));
	skillButton->SetSize(buttonSize - (margin / 2.0f));

	fleeButton->SetLocalPosition(glm::vec2(buttonSize.x / 2.0f, buttonSize.y));
	fleeButton->SetSize(buttonSize - (margin / 2.0f));
}