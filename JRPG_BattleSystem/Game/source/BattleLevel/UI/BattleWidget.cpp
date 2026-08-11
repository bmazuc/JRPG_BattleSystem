#include "BattleLevel/UI/BattleWidget.h"
#include "UI/Text.h"
#include "World/Level/Scene/Scene.h"
#include "Components/Camera/CameraComponent.h"
#include "UI/Image.h"
#include "Rendering/Material.h"
#include "BattleLevel/UI/CharacterInfosText.h"

void BattleWidget::Construct()
{
	turnText = CreateWidget<Text>("TurnText", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(100, 20)));
	turnText->SetSize(24);

	infosBackground = CreateWidget<Image>("InfosBackground", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(220, 385)));
	infosBackground->SetSize(glm::vec2(400, 150));
	infosBackground->GetMaterial()->SetTexture(infosBackgroundTextureName);
}

void BattleWidget::InitCharacterInfos(std::vector<Character*> characters)
{
	glm::vec2 position = glm::vec2(80, 345);
	for (Character* character : characters)
	{
		CharacterInfosText* t = CreateWidget<CharacterInfosText>("CharacterInfosText", UISpawnInfo(nullptr, TransformSpace::World, position));
		t->SetSize(20);
		t->AssociateCharacter(character);
		t->SetIsCenterX(false);
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

		glm::vec4 color = damageTextData.text->GetColor();
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