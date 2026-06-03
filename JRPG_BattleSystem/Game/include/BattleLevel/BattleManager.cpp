#include "BattleManager.h"
#include "BattleLevel/EnemySpawner.h"

void BattleManager::Initialize()
{
	SpawnEnemies();
}

void BattleManager::SpawnEnemies()
{
	if (enemySpawner)
	{
		std::vector<Enemy*> enemies = enemySpawner->GenerateEnemies();
		for (Enemy* enemy : enemies)
		{
			enemy->OnSelected.Bind(this, &BattleManager::OnEnemySelected);
			enemy->OnDeath.Bind(this, &BattleManager::OnEnemyDeath);
		}
		aliveEnemiesCount = enemies.size();
	}
}

void BattleManager::OnEnemyDeath()
{
	--aliveEnemiesCount;
	if (aliveEnemiesCount <= 0)
	{
		SpawnEnemies();
	}
}

void BattleManager::OnEnemySelected(Enemy* selectedEnemy)
{
	selectedEnemy->Kill();
}