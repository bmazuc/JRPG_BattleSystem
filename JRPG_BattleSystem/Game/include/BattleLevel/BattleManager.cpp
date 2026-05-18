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
			enemy->OnDeath.Bind(std::bind(&BattleManager::OnEnemyDeath, this));
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
