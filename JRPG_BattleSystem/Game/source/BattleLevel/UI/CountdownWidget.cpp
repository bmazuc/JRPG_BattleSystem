#include "BattleLevel/UI/CountdownWidget.h"
#include "UI/Text.h"

void CountdownWidget::Construct()
{
	countdownText = CreateWidget<Text>("TurnText", UISpawnInfo(nullptr, TransformSpace::Local));
	countdownText->SetContent(std::to_string(count));
	countdownText->SetSize(24.0f);

	timer = inBetweenCountDuration;
}

void CountdownWidget::Update(float deltaTime)
{
	timer -= deltaTime;
	if (timer <= 0.0f)
	{
		count -= 1;
		if (count < 0)
		{
			OnCountdownEnd.Call();
			MarkForDestruction();
		}
		else if (count == 0)
		{
			countdownText->SetContent("Start");
			timer = inBetweenCountDuration;
		}
		else
		{
			countdownText->SetContent(std::to_string(count));
			timer = inBetweenCountDuration;
		}
	}
}