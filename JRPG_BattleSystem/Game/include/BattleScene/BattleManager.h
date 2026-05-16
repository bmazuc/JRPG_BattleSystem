#pragma once

#include "Scene\SceneSubsystem.h"

class EnemySpawner;

class BattleManager : public SceneSubsystem
{
public:
	void Initialize() override;

	void SetEnemySpawner(EnemySpawner* newEnemySpawner) { enemySpawner = newEnemySpawner; }

private:
	void SpawnEnemies();
	void OnEnemyDeath();

	EnemySpawner* enemySpawner;
	unsigned int aliveEnemiesCount = 0;
};

