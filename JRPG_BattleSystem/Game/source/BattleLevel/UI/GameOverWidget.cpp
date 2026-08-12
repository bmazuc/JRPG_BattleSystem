#include "BattleLevel/UI/GameOverWidget.h"
#include "UI/Text.h"
#include "Common/UI/LoadLevelButton.h"
#include "Rendering/Material.h"

void GameOverWidget::Construct()
{
	text = CreateWidget<Text>("GameOverText", UISpawnInfo(nullptr, TransformSpace::Local,glm::vec2(0, -30)));
	text->SetSize(24);

	LoadLevelButton* mainMenuButton = CreateWidget<LoadLevelButton>("MainMenuButton", UISpawnInfo(nullptr, TransformSpace::Local, glm::vec2(0, 30)));
	mainMenuButton->GetMaterial()->SetTexture("button");
	mainMenuButton->SetSize(glm::vec2(150, 50));
	mainMenuButton->SetLevelToLoad("mainMenu");

	Text* mainMenuButtonText = CreateWidget<Text>("MainMenuButtonText", UISpawnInfo(mainMenuButton, TransformSpace::Local));
	mainMenuButtonText->SetContent("Main Menu");
	mainMenuButtonText->SetSize(24);
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