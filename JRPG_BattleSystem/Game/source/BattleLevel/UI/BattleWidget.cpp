#include "BattleLevel/UI/BattleWidget.h"
#include "UI/Text.h"
#include "World/Level/Scene/Scene.h"
#include "Components/Camera/CameraComponent.h"
#include "UI/Image.h"
#include "Rendering/Material.h"
#include "BattleLevel/UI/CharacterInfosText.h"
#include "BattleLevel/UI/PlayerActionsMenu/PlayerActionsMenu.h"
#include "BattleLevel/Characters/PlayerCharacter.h"

void BattleWidget::Construct()
{
	turnText = CreateWidget<Text>("TurnText", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(100, 20)));
	turnText->SetSize(24);

	infosBackground = CreateWidget<Image>("InfosBackground", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(220, 385)));
	infosBackground->SetSize(glm::vec2(400, 150));
	infosBackground->GetMaterial()->SetTexture(infosBackgroundTextureName);

	playerActionsMenu = CreateWidget<PlayerActionsMenu>("PlayerActionsMenu", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(440, 385)));
	playerActionsMenu->SetSize(glm::vec2(180, 150));
	playerActionsMenu->SetMargin(glm::vec2(4.0f, 4.0f));
	playerActionsMenu->SetVisible(false);
}

void BattleWidget::InitCharacterInfos(std::vector<PlayerCharacter*> characters)
{
	glm::vec2 position = glm::vec2(80, 345);
	for (PlayerCharacter* character : characters)
	{
		CharacterInfosText* text = CreateWidget<CharacterInfosText>("CharacterInfosText", UISpawnInfo(nullptr, TransformSpace::World, position));
		text->SetSize(15);
		text->AssociateCharacter(character);
		text->SetIsCenterX(false);
		position.y += 30;
	}
}

void BattleWidget::Update(float deltaTime)
{
	int damageTextCount = (int)currentDamageTextDisplayed.size();
	for (int i = damageTextCount - 1; i >= 0; i--)
	{
		DamageDisplayTextData& damageTextData = currentDamageTextDisplayed[i];

		damageTextData.lifeTime += deltaTime;

		Color color = damageTextData.text->GetColor();
		color.a = 1.0f - damageTextData.lifeTime / damageTextDuration;
		damageTextData.text->SetColor(color);

		glm::vec2 pos = damageTextData.text->GetWorldPosition();
		pos.y -= damageTextSpeed * deltaTime;
		damageTextData.text->SetWorldPosition(pos);

		if (color.a <= 0.0f)
		{
			damageTextData.text->MarkForDestruction();
			currentDamageTextDisplayed.erase(currentDamageTextDisplayed.begin() + i);
		}
	}

	if (damageTextCount > 0 && currentDamageTextDisplayed.size() <= 0)
	{
		OnAllDamageTextDestroy.Call();
	}
}

void BattleWidget::SetTurnText(std::string content)
{
	if (turnText)
	{
		turnText->SetContent(content);
	}
}

void BattleWidget::DisplayDamage(glm::vec2 worldPosition, int damageTaken)
{
	if (currentScene)
	{
		glm::vec2 screenPosition = currentScene->GetActiveCamera()->WorldToScreen(worldPosition);
		Text* text = CreateWidget<Text>("DamageText", UISpawnInfo(nullptr, TransformSpace::World, screenPosition));
		text->SetSize(24);
		text->SetContent(std::to_string(damageTaken));

		currentDamageTextDisplayed.push_back(DamageDisplayTextData(text));
	}
}

void BattleWidget::ShowPlayerActionsMenu(PlayerCharacter* character)
{
	if (playerActionsMenu)
	{
		playerActionsMenu->Show(character);
	}
}

void BattleWidget::HidePlayerActionsMenu()
{
	if (playerActionsMenu)
	{
		playerActionsMenu->Hide();
	}
}