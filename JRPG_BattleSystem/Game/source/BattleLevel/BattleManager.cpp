#include "BattleLevel/BattleManager.h"
#include "BattleLevel/Spawners/EnemySpawner.h"
#include "BattleLevel/Spawners/PlayerSpawner.h"
#include "Core/Random.h"
#include "UI/Text.h"

void BattleManager::Initialize()
{
	SpawnPlayerCharacters();
	SpawnEnemies();
	StartNextBattle();
}

void BattleManager::Update(float deltaTime)
{
	if (currentTurn == TurnType::EnemyTurn)
	{
		timer -= deltaTime;
		if (timer <= 0.0f)
		{
			int index = Random::FromRange(0, playerCharacters.size() - 1);
			playerCharacters[index]->Kill();
			NextTurn();
		}
	}
}

void BattleManager::SpawnPlayerCharacters()
{
	if (playerSpawner)
	{
		playerCharacters = playerSpawner->GeneratePlayerGroup();
		for (Character* playerCharacter : playerCharacters)
		{
			playerCharacter->OnDeath.Bind(this, &BattleManager::OnPlayerCharacterDeath);
		}
	}
}

void BattleManager::SpawnEnemies()
{
	if (enemySpawner)
	{
		enemies = enemySpawner->GenerateEnemies();
		for (Enemy* enemy : enemies)
		{
			enemy->OnSelected.Bind(this, &BattleManager::OnEnemySelected);
			enemy->OnDeath.Bind(this, &BattleManager::OnEnemyDeath);
		}
	}
}

void BattleManager::GenerateTurnOrder()
{
	turnOrder.clear();
	for (Character* playerCharacter : playerCharacters)
	{
		turnOrder.push_back(playerCharacter);
	}
	for (Enemy* enemy : enemies)
	{
		turnOrder.push_back(enemy);
	}

	Random::ShuffleVector(turnOrder);

	NextTurn();
}

void BattleManager::NextTurn()
{
	Character* currentCharacter = turnOrder[turnIndex];

	if (dynamic_cast<Enemy*>(currentCharacter))
	{
		InitEnemyTurn();
	}
	else
	{
		InitPlayerTurn();
	}

	turnIndex = (turnIndex + 1) % turnOrder.size();
}

void BattleManager::InitPlayerTurn()
{
	currentTurn = TurnType::PlayerTurn;
	if (turnText)
	{
		turnText->SetContent("Player Turn");
	}
}

void BattleManager::InitEnemyTurn()
{
	currentTurn = TurnType::EnemyTurn;
	if (turnText)
	{
		turnText->SetContent("Enemy Turn");
	}
	timer = 2.0f;
}

void BattleManager::OnPlayerCharacterDeath(Character* playerCharacter)
{
	turnOrder.erase(std::remove(turnOrder.begin(), turnOrder.end(), playerCharacter), turnOrder.end());

	if (turnIndex >= turnOrder.size())
	{
		turnIndex = 0;
	}

	playerCharacters.erase(std::remove(playerCharacters.begin(), playerCharacters.end(), playerCharacter), playerCharacters.end());
	if (playerCharacters.size() <= 0)
	{
		SpawnPlayerCharacters();
		StartNextBattle();
	}
}

void BattleManager::OnEnemyDeath(Character* enemy)
{
	turnOrder.erase(std::remove(turnOrder.begin(), turnOrder.end(), enemy), turnOrder.end());

	if (turnIndex >= turnOrder.size())
	{
		turnIndex = 0;
	}

	enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
	if (enemies.size() <= 0)
	{
		SpawnEnemies();
		StartNextBattle();
	}
}

void BattleManager::OnEnemySelected(Enemy* selectedEnemy)
{
	if (currentTurn == TurnType::PlayerTurn)
	{
		selectedEnemy->Kill();
		NextTurn();
	}
}

void BattleManager::StartNextBattle()
{
	turnIndex = 0;
	GenerateTurnOrder();
}