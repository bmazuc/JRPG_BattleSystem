#include "BattleWidget.h"
#include "UI/Text.h"
#include "BattleLevel/BattleManager.h"
#include "World/Level/Scene/Scene.h"
#include "Components/Camera/CameraComponent.h"

void BattleWidget::Construct()
{
	turnText = CreateWidget<Text>("TurnText", UISpawnInfo(nullptr, TransformSpace::World, glm::vec2(100, 20)));
	turnText->SetSize(24);
	if (currentTurnType != TurnType::None)
	{
		turnText->SetContent(currentTurnType == TurnType::PlayerTurn ? "Player Turn" : "Enemy Turn");
	}
}

void BattleWidget::Update(float deltaTime)
{
	int damageTextCount = currentDamageTextDisplayed.size();
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

void BattleWidget::SetTurnText(TurnType turnType)
{
	currentTurnType = turnType;

	if (turnText)
	{
		turnText->SetContent(turnType == TurnType::PlayerTurn ? "Player Turn" : "Enemy Turn");
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