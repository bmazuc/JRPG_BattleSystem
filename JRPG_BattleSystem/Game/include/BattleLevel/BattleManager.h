#ifndef __BATTLE_MANAGER_H_INCLUDED__
#define __BATTLE_MANAGER_H_INCLUDED__

#include "World/Level/LevelSubsystem.h"

class EnemySpawner;
class Enemy;

class BattleManager : public LevelSubsystem
{
public:
	void Initialize() override;

	void SetEnemySpawner(EnemySpawner* newEnemySpawner) { enemySpawner = newEnemySpawner; }

private:
	void SpawnEnemies();
	void OnEnemyDeath();

	void OnEnemySelected(Enemy* selectedEnemy);

	EnemySpawner* enemySpawner;
	size_t aliveEnemiesCount = 0;
};

#endif // __BATTLE_MANAGER_H_INCLUDED__