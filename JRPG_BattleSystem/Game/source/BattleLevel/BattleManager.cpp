#include "BattleLevel/BattleManager.h"
#include "BattleLevel/Spawners/EnemySpawner.h"
#include "BattleLevel/Spawners/PlayerSpawner.h"
#include "Core/Random.h"
#include "BattleLevel/UI/BattleWidget.h"

void BattleManager::Initialize()
{
	SpawnPlayerCharacters();
	SpawnEnemies();
	GenerateTurnOrder();
	NextTurn();
}

void BattleManager::Update(float deltaTime)
{
	if (currentTurn == TurnType::EnemyTurn)
	{
		currentEnemyTurnDuration -= deltaTime;
		if (currentEnemyTurnDuration <= 0.0f && !resolvingTurn)
		{
			int index = Random::FromRange(0, (int)playerCharacters.size() - 1);
			InflictDamage(currentCharacter, playerCharacters[index]);
		}
	}
}

void BattleManager::SetBattleWidget(BattleWidget* widget) 
{ 
	if (battleWidget)
	{
		battleWidget->OnAllDamageTextDestroy.Unbind(OnAllDamageTextDestroyHandle);
	}

	battleWidget = widget; 

	if (battleWidget)
	{
		battleWidget->SetDamageTextDuration(battleConfig.damageTextDuration);
		battleWidget->SetDamageTextSpeed(battleConfig.damageTextSpeed);

		OnAllDamageTextDestroyHandle = battleWidget->OnAllDamageTextDestroy.Bind(this, &BattleManager::OnAllDamageTextDestroy);
	}
}

void BattleManager::SpawnPlayerCharacters()
{
	if (playerSpawner)
	{
		playerCharacters = playerSpawner->GeneratePlayerGroup();
		for (Character* playerCharacter : playerCharacters)
		{
			playerCharacter->SetDamageDuration(battleConfig.blinkDuration);

			playerCharacter->OnDamageTaken.Bind(this, &BattleManager::OnCharacterTakeDamage);
			playerCharacter->OnBlinkEnd.Bind(this, &BattleManager::OnBlinkEnd);
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
			enemy->SetDamageDuration(battleConfig.blinkDuration);

			enemy->OnSelected.Bind(this, &BattleManager::OnEnemySelected);
			enemy->OnDamageTaken.Bind(this, &BattleManager::OnCharacterTakeDamage);
			enemy->OnBlinkEnd.Bind(this, &BattleManager::OnBlinkEnd);
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
}

void BattleManager::OnAllDamageTextDestroy()
{
	waitingForDamageTextDestroy = false;
	NextTurn();
}

void BattleManager::NextTurn()
{
	if (waitingForBlinkEnd || waitingForDamageTextDestroy)
	{
		return;
	}

	if (enemies.size() == 0)
	{
		SpawnEnemies();
		turnIndex = 0;
		GenerateTurnOrder();
	}
	else if (playerCharacters.size() == 0)
	{
		SpawnPlayerCharacters();
		turnIndex = 0;
		GenerateTurnOrder();
	}

	currentCharacter = turnOrder[turnIndex];

	if (dynamic_cast<Enemy*>(currentCharacter))
	{
		InitEnemyTurn();
	}
	else
	{
		InitPlayerTurn();
	}

	turnIndex = (turnIndex + 1) % turnOrder.size();
	resolvingTurn = false;
}

void BattleManager::InitPlayerTurn()
{
	currentTurn = TurnType::PlayerTurn;
	if (battleWidget)
	{
		battleWidget->SetTurnText(currentTurn);
	}
}

void BattleManager::InitEnemyTurn()
{
	currentTurn = TurnType::EnemyTurn;
	if (battleWidget)
	{
		battleWidget->SetTurnText(currentTurn);
	}
	currentEnemyTurnDuration = battleConfig.enemyTurnDuration;
}

void BattleManager::OnCharacterTakeDamage(Character* character, int damageTaken)
{
	if (battleWidget)
	{
		battleWidget->DisplayDamage(character->GetWorldPosition(), damageTaken);
	}
}

void BattleManager::OnPlayerCharacterDeath(Character* playerCharacter)
{
	turnOrder.erase(std::remove(turnOrder.begin(), turnOrder.end(), playerCharacter), turnOrder.end());

	if (turnIndex >= turnOrder.size())
	{
		turnIndex = 0;
	}

	playerCharacters.erase(std::remove(playerCharacters.begin(), playerCharacters.end(), playerCharacter), playerCharacters.end());
}

void BattleManager::OnEnemyDeath(Character* enemy)
{

	turnOrder.erase(std::remove(turnOrder.begin(), turnOrder.end(), enemy), turnOrder.end());

	if (turnIndex >= turnOrder.size())
	{
		turnIndex = 0;
	}

	enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
}

void BattleManager::OnBlinkEnd()
{
	waitingForBlinkEnd = false;
	NextTurn();
}

void BattleManager::OnEnemySelected(Enemy* selectedEnemy)
{
	if (currentTurn == TurnType::PlayerTurn && !resolvingTurn)
	{
		InflictDamage(currentCharacter, selectedEnemy);
	}
}

void BattleManager::InflictDamage(Character* attacker, Character* defender)
{
	resolvingTurn = true;
	waitingForBlinkEnd = true;
	waitingForDamageTextDestroy = true;

	int damages = std::max(0, attacker->GetAttributes().attack - defender->GetAttributes().defense);

	defender->TakeDamage(damages);
}