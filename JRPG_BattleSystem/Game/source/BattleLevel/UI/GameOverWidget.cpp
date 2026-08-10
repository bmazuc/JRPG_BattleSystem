#include "BattleLevel/UI/GameOverWidget.h"
#include "UI/Text.h"

void GameOverWidget::Construct()
{
	text = CreateWidget<Text>("GameOverText", UISpawnInfo(nullptr, TransformSpace::Local));
	text->SetSize(24);
}

void GameOverWidget::SetKillCount(int killCount)
{
	if (text)
	{
		std::string gameOverText = "You have killed ";
		gameOverText += std::to_string(killCount);
		gameOverText += (killCount > 1) ? " enemies" : " enemy.";

		text->SetContent(gameOverText);
	}
}